#include "serial_interface.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "mavlink_cpp/all/mavlink.h"
#include <chrono>

#define HEARTBEAT_RATE_MS 1000


Serial_Interface::Serial_Interface()
{
    setup_serial();
}

void Serial_Interface::setup_serial()
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
}

void Serial_Interface::send_message(uint16_t len, uint8_t* msg)
{
    uart_write_bytes_with_break(ECHO_UART_PORT_NUM, (const char*)msg, len, 100);
}

uint32_t Serial_Interface::get_millis_ms()
{
	return esp_timer_get_time()/1000ULL;
}

void Serial_Interface::send_heartbeat(uint8_t component_id, uint32_t rate_ms)
{
    auto millis = get_millis_ms();
    if ((millis - last_heartbeat_ms) < rate_ms) {
        return;
    }
    last_heartbeat_ms = millis;
    uint8_t buf[1000];
    mavlink_message_t mav_msg;
    mavlink_msg_heartbeat_pack(1, component_id, &mav_msg, MAV_TYPE_ONBOARD_CONTROLLER, MAV_AUTOPILOT_GENERIC, 0, 0, 0);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &mav_msg);
    send_message(len, buf);
}