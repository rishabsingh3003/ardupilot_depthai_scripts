// MESSAGE RADIO_CALIBRATION support class

#pragma once

namespace mavlink {
namespace ualberta {
namespace msg {

/**
 * @brief RADIO_CALIBRATION message
 *
 * Complete set of calibration parameters for the radio
 */
struct RADIO_CALIBRATION : mavlink::Message {
    static constexpr msgid_t MSG_ID = 221;
    static constexpr size_t LENGTH = 42;
    static constexpr size_t MIN_LENGTH = 42;
    static constexpr uint8_t CRC_EXTRA = 71;
    static constexpr auto NAME = "RADIO_CALIBRATION";


    std::array<uint16_t, 3> aileron; /*<  Aileron setpoints: left, center, right */
    std::array<uint16_t, 3> elevator; /*<  Elevator setpoints: nose down, center, nose up */
    std::array<uint16_t, 3> rudder; /*<  Rudder setpoints: nose left, center, nose right */
    std::array<uint16_t, 2> gyro; /*<  Tail gyro mode/gain setpoints: heading hold, rate mode */
    std::array<uint16_t, 5> pitch; /*<  Pitch curve setpoints (every 25%) */
    std::array<uint16_t, 5> throttle; /*<  Throttle curve setpoints (every 25%) */


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
        ss << "  aileron: [" << to_string(aileron) << "]" << std::endl;
        ss << "  elevator: [" << to_string(elevator) << "]" << std::endl;
        ss << "  rudder: [" << to_string(rudder) << "]" << std::endl;
        ss << "  gyro: [" << to_string(gyro) << "]" << std::endl;
        ss << "  pitch: [" << to_string(pitch) << "]" << std::endl;
        ss << "  throttle: [" << to_string(throttle) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << aileron;                       // offset: 0
        map << elevator;                      // offset: 6
        map << rudder;                        // offset: 12
        map << gyro;                          // offset: 18
        map << pitch;                         // offset: 22
        map << throttle;                      // offset: 32
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> aileron;                       // offset: 0
        map >> elevator;                      // offset: 6
        map >> rudder;                        // offset: 12
        map >> gyro;                          // offset: 18
        map >> pitch;                         // offset: 22
        map >> throttle;                      // offset: 32
    }
};

} // namespace msg
} // namespace ualberta
} // namespace mavlink
