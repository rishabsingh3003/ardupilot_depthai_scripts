#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstring>

#include "decode_raw_mobilenet.h"
#include "esp32_spi_impl.h"

#include "spi_api.hpp"


#include "mavlink_cpp/all/mavlink.h"
#include "serial_interface/serial_interface.h"
#include <chrono>

class follow_me
{
public:

    void main_loop();

private:

    void send_position_target(uint32_t time, float x, float y, float z);

    // set serial port for mavlink communication
    Serial_Interface serial_comm;

    const std::string status[4] = {"New", "Tracked", "Lost", "Removed"};
};