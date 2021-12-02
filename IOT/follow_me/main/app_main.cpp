#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <chrono>

extern "C"
{
   void app_main();
}

#include "app_main.h"

void follow_me::send_position_target(uint32_t time, float x, float y, float z)
{
    const float pos_target[3] = {z * 0.001f ,x * 0.001f,-y * 0.001f};
    const float pos_target_offset[3] = {pos_target[0]-2.5f, pos_target[1], pos_target[2]-0.75f};
    uint8_t buf[2041];
    mavlink_message_t mav_msg;
    mavlink_msg_set_position_target_local_ned_pack(1, 93, &mav_msg, time, 0, 0, MAV_FRAME_BODY_OFFSET_NED, 0b0111110111111000, pos_target_offset[0], pos_target_offset[1], pos_target_offset[2], 0,0,0,0,0,0,0,0);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &mav_msg);
    serial_comm.send_message(len, buf);
}

void follow_me::main_loop()
{
    uint8_t req_success = 0;

    dai::SpiApi mySpiApi;
    mySpiApi.set_send_spi_impl(&esp32_send_spi);
    mySpiApi.set_recv_spi_impl(&esp32_recv_spi);

    while(true) {

        // send heartbeat to ArduPilot at a constant rate
        serial_comm.send_heartbeat();

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
                    send_position_target(serial_comm.get_millis_ms(), t.spatialCoordinates.x, t.spatialCoordinates.y, t.spatialCoordinates.z);
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

    follow_me follow_me_spi;

    // run the main loop
    follow_me_spi.main_loop();

    //Never reached.
    deinit_esp32_spi();
}
