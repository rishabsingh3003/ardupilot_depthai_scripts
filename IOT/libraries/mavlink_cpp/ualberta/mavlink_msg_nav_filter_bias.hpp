// MESSAGE NAV_FILTER_BIAS support class

#pragma once

namespace mavlink {
namespace ualberta {
namespace msg {

/**
 * @brief NAV_FILTER_BIAS message
 *
 * Accelerometer and Gyro biases from the navigation filter
 */
struct NAV_FILTER_BIAS : mavlink::Message {
    static constexpr msgid_t MSG_ID = 220;
    static constexpr size_t LENGTH = 32;
    static constexpr size_t MIN_LENGTH = 32;
    static constexpr uint8_t CRC_EXTRA = 34;
    static constexpr auto NAME = "NAV_FILTER_BIAS";


    uint64_t usec; /*<  Timestamp (microseconds) */
    float accel_0; /*<  b_f[0] */
    float accel_1; /*<  b_f[1] */
    float accel_2; /*<  b_f[2] */
    float gyro_0; /*<  b_f[0] */
    float gyro_1; /*<  b_f[1] */
    float gyro_2; /*<  b_f[2] */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  usec: " << usec << std::endl;
        ss << "  accel_0: " << accel_0 << std::endl;
        ss << "  accel_1: " << accel_1 << std::endl;
        ss << "  accel_2: " << accel_2 << std::endl;
        ss << "  gyro_0: " << gyro_0 << std::endl;
        ss << "  gyro_1: " << gyro_1 << std::endl;
        ss << "  gyro_2: " << gyro_2 << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << usec;                          // offset: 0
        map << accel_0;                       // offset: 8
        map << accel_1;                       // offset: 12
        map << accel_2;                       // offset: 16
        map << gyro_0;                        // offset: 20
        map << gyro_1;                        // offset: 24
        map << gyro_2;                        // offset: 28
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> usec;                          // offset: 0
        map >> accel_0;                       // offset: 8
        map >> accel_1;                       // offset: 12
        map >> accel_2;                       // offset: 16
        map >> gyro_0;                        // offset: 20
        map >> gyro_1;                        // offset: 24
        map >> gyro_2;                        // offset: 28
    }
};

} // namespace msg
} // namespace ualberta
} // namespace mavlink
