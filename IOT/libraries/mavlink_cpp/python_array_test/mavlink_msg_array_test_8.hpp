// MESSAGE ARRAY_TEST_8 support class

#pragma once

namespace mavlink {
namespace python_array_test {
namespace msg {

/**
 * @brief ARRAY_TEST_8 message
 *
 * Array test #8.
 */
struct ARRAY_TEST_8 : mavlink::Message {
    static constexpr msgid_t MSG_ID = 17158;
    static constexpr size_t LENGTH = 24;
    static constexpr size_t MIN_LENGTH = 24;
    static constexpr uint8_t CRC_EXTRA = 106;
    static constexpr auto NAME = "ARRAY_TEST_8";


    uint32_t v3; /*<  Stub field */
    std::array<double, 2> ar_d; /*<  Value array */
    std::array<uint16_t, 2> ar_u16; /*<  Value array */


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
        ss << "  v3: " << v3 << std::endl;
        ss << "  ar_d: [" << to_string(ar_d) << "]" << std::endl;
        ss << "  ar_u16: [" << to_string(ar_u16) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << ar_d;                          // offset: 0
        map << v3;                            // offset: 16
        map << ar_u16;                        // offset: 20
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> ar_d;                          // offset: 0
        map >> v3;                            // offset: 16
        map >> ar_u16;                        // offset: 20
    }
};

} // namespace msg
} // namespace python_array_test
} // namespace mavlink
