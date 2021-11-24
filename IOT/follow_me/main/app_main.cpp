#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstring>

#include "decode_raw_mobilenet.h"
#include "esp32_spi_impl.h"

#include "spi_api.hpp"


#include "mavlink_cpp/all/mavlink.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include <chrono>


extern "C"
{
   void app_main();
}

const std::string status[4] = {"New", "Tracked", "Lost", "Removed"};


#define ECHO_TEST_TXD 17
#define ECHO_TEST_RXD 16
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define ECHO_UART_PORT_NUM      (UART_NUM_2)
#define ECHO_UART_BAUD_RATE     (115200)
#define ECHO_TASK_STACK_SIZE    (CONFIG_EXAMPLE_TASK_STACK_SIZE)

#define BUF_SIZE (1024)

#define HEARTBEAT_RATE_MS 1000

uint32_t last_heartbeat_ms = 0;

static void setup_serial()
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = ECHO_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    int intr_alloc_flags = 0;

#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif

    ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));

    // Configure a temporary buffer for the incoming data
    // uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
}

uint32_t get_millis_ms() {
	using namespace std::chrono;
	return static_cast<uint32_t>(duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()).count());
}

void send_heartbeat()
{
    const uint32_t millis = get_millis_ms();
    if ((millis - last_heartbeat_ms) < 1000) {
        return;
    }
    last_heartbeat_ms = millis;
    uint8_t buf[2041];
    mavlink_message_t mav_msg;
    mavlink_msg_heartbeat_pack(1, 93, &mav_msg, MAV_TYPE_ONBOARD_CONTROLLER, MAV_AUTOPILOT_GENERIC, 0, 0, 0);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &mav_msg);
    uart_write_bytes_with_break(ECHO_UART_PORT_NUM, (const char*)buf, len, 100);
}

void send_position_target(uint32_t time, float x, float y, float z)
{
    const float pos_target[3] = {z * 0.001f ,x * 0.001f,-y * 0.001f};
    const float pos_target_offset[3] = {pos_target[0]-2.5f, pos_target[1], pos_target[2]-0.75f};
    uint8_t buf[2041];
    mavlink_message_t mav_msg;
    mavlink_msg_set_position_target_local_ned_pack(1, 93, &mav_msg, time, 0, 0, MAV_FRAME_BODY_OFFSET_NED, 0b0111110111111000, pos_target_offset[0], pos_target_offset[1], pos_target_offset[2], 0,0,0,0,0,0,0,0);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &mav_msg);
    uart_write_bytes_with_break(ECHO_UART_PORT_NUM, (const char*)buf, len, 100);
}

void main_loop()
{
    uint8_t req_success = 0;

    dai::SpiApi mySpiApi;
    mySpiApi.set_send_spi_impl(&esp32_send_spi);
    mySpiApi.set_recv_spi_impl(&esp32_recv_spi);

    while(1) {

        // send heartbeat to ArduPilot
        send_heartbeat();

        // ----------------------------------------
        // basic example of receiving tracklets from the MyriadX
        // ----------------------------------------
        dai::Message msg;
        if(mySpiApi.req_message(&msg, "tracklets")){
            // example of parsing the raw metadata
            dai::RawTracklets tracklets;
            mySpiApi.parse_metadata(&msg.raw_meta, tracklets);
            for(const auto& t : tracklets.tracklets){
                if ((std::int32_t)t.status == 1) {
                    // first tracked object
                    printf("ID: %d, Status: %s, x: %f, y: %f, z: %f \n",
                    t.id, status[(std::int32_t)t.status].c_str(),
                    t.spatialCoordinates.x, t.spatialCoordinates.y,
                    t.spatialCoordinates.z);
                    // send position mavlink message
                    send_position_target(get_millis_ms(), t.spatialCoordinates.x, t.spatialCoordinates.y, t.spatialCoordinates.z);
                    break;
                }
            }

            // free up resources once you're done with the message.
            mySpiApi.free_message(&msg);
        }

        // ----------------------------------------
        // pop current message/metadata. this tells the depthai to update the info being passed back using the spi_cmds.
        // ----------------------------------------
        req_success = mySpiApi.spi_pop_messages();
    }
}

//Main application
void app_main()
{
    // init spi for the esp32
    init_esp32_spi();

    // set serial port for mavlink communication
    setup_serial();

    // run the main loop
    main_loop();

    //Never reached.
    deinit_esp32_spi();
}
