#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <chrono>

#define OBSTACLE_SEND_RATE_HZ 15

extern "C"
{
   void app_main();
}

#include "app_main.h"

void obstacle_avoidance::send_obs_dist_3d(uint32_t time, float x, float y, float z)
{
    const float obstacle_vector[3] = {z * 0.001f ,x * 0.001f,-y * 0.001f};
    uint8_t buf[2041];
    mavlink_message_t mav_msg;
    mavlink_msg_obstacle_distance_3d_pack(1, 93, &mav_msg, time, 0, MAV_FRAME_BODY_FRD, 65535, obstacle_vector[0], obstacle_vector[1], obstacle_vector[2], 0.3f, 10.0f);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &mav_msg);
    serial_comm.send_message(len, buf);
}

void obstacle_avoidance::main_loop()
{
    uint8_t req_success = 0;

    dai::SpiApi mySpiApi;
    mySpiApi.set_send_spi_impl(&esp32_send_spi);
    mySpiApi.set_recv_spi_impl(&esp32_recv_spi);

    while(true) {

        // send heartbeat to ArduPilot at a constant rate
        serial_comm.send_heartbeat();

        dai::Message spatialDataMsg;
        bool receivedAnyMessage = false;

        if(mySpiApi.req_message(&spatialDataMsg, "spatialData")){
            // example of parsing the raw metadata
            const uint32_t msg_ms = serial_comm.get_millis_ms();
            dai::RawSpatialLocations rawSpatialLocations;
            mySpiApi.parse_metadata(&spatialDataMsg.raw_meta, rawSpatialLocations);

            if ((last_obstacle_msg_ms - msg_ms) > 1000/OBSTACLE_SEND_RATE_HZ) {
                last_obstacle_msg_ms = msg_ms;
                int i = 0;
                for(const auto& spatialData : rawSpatialLocations.spatialLocations){
                    auto x = spatialData.spatialCoordinates.x;
                    auto y = spatialData.spatialCoordinates.y;
                    auto z = spatialData.spatialCoordinates.z;
                    send_obs_dist_3d(msg_ms, x, y, z);
                    auto euclideanDistance = std::sqrt(x*x + y*y + z*z);
                    printf("Euclidean distance %d mm, X: %d mm, Y: %d mm, Z: %d mm \n",(int)euclideanDistance,(int)x,(int)y,(int)z);
                }
            }
            // free up resources once you're done with the message.
            mySpiApi.free_message(&spatialDataMsg);
            mySpiApi.spi_pop_message("spatialData");
            receivedAnyMessage = true;
        }

        if(!receivedAnyMessage) {
            // Delay pooling of messages
            usleep(1000);
        }
    }
}

//Main application
void app_main()
{
    // init spi for the esp32
    init_esp32_spi();

    obstacle_avoidance avoidance_grid;

    // run the main loop
    avoidance_grid.main_loop();

    //Never reached.
    deinit_esp32_spi();
}
