// MESSAGE UALBERTA_SYS_STATUS support class

#pragma once

namespace mavlink {
namespace ualberta {
namespace msg {

/**
 * @brief UALBERTA_SYS_STATUS message
 *
 * System status specific to ualberta uav
 */
struct UALBERTA_SYS_STATUS : mavlink::Message {
    static constexpr msgid_t MSG_ID = 222;
    static constexpr size_t LENGTH = 3;
    static constexpr size_t MIN_LENGTH = 3;
    static constexpr uint8_t CRC_EXTRA = 15;
    static constexpr auto NAME = "UALBERTA_SYS_STATUS";


    uint8_t mode; /*<  System mode, see UALBERTA_AUTOPILOT_MODE ENUM */
    uint8_t nav_mode; /*<  Navigation mode, see UALBERTA_NAV_MODE ENUM */
    uint8_t pilot; /*<  Pilot mode, see UALBERTA_PILOT_MODE */


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
        ss << "  mode: " << +mode << std::endl;
        ss << "  nav_mode: " << +nav_mode << std::endl;
        ss << "  pilot: " << +pilot << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << mode;                          // offset: 0
        map << nav_mode;                      // offset: 1
        map << pilot;                         // offset: 2
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> mode;                          // offset: 0
        map >> nav_mode;                      // offset: 1
        map >> pilot;                         // offset: 2
    }
};

} // namespace msg
} // namespace ualberta
} // namespace mavlink
