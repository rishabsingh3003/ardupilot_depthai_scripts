#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cmath>


extern "C"
{
   void app_main();
}

#include "app_main.h"

void prec_land::send_landing_target(uint32_t time, float x, float y, float z)
{
    const float land_target[3] = {-z * 0.001f ,y * 0.001f, x * 0.001f};
    const float x_offset_rad = atan2(-land_target[2], land_target[0]);
    const float y_offset_rad = atan2(land_target[1], land_target[0]);
    const float land_dist = sqrt(pow(land_target[0], 2) +  pow(land_target[1], 2) + pow(land_target[2], 2));
    uint8_t buf[1000];
    mavlink_message_t mav_msg;
    mavlink_msg_landing_target_pack(1, 93, &mav_msg, time, 0, 0, x_offset_rad, y_offset_rad, land_dist, 0,0,0,0,0,0,0,0);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &mav_msg);
    serial_comm.send_message(len, buf);
}

void prec_land::main_loop()
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
                    send_landing_target(serial_comm.get_millis_ms(), t.spatialCoordinates.x, t.spatialCoordinates.y, t.spatialCoordinates.z);
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

    prec_land prec_land_spi;

    // run the main loop
    prec_land_spi.main_loop();

    //Never reached.
    deinit_esp32_spi();
}
