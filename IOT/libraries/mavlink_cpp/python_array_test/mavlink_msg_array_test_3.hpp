// MESSAGE ARRAY_TEST_3 support class

#pragma once

namespace mavlink {
namespace python_array_test {
namespace msg {

/**
 * @brief ARRAY_TEST_3 message
 *
 * Array test #3.
 */
struct ARRAY_TEST_3 : mavlink::Message {
    static constexpr msgid_t MSG_ID = 17153;
    static constexpr size_t LENGTH = 17;
    static constexpr size_t MIN_LENGTH = 17;
    static constexpr uint8_t CRC_EXTRA = 19;
    static constexpr auto NAME = "ARRAY_TEST_3";


    uint8_t v; /*<  Stub field */
    std::array<uint32_t, 4> ar_u32; /*<  Value array */


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
        ss << "  v: " << +v << std::endl;
        ss << "  ar_u32: [" << to_string(ar_u32) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << ar_u32;                        // offset: 0
        map << v;                             // offset: 16
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> ar_u32;                        // offset: 0
        map >> v;                             // offset: 16
    }
};

} // namespace msg
} // namespace python_array_test
} // namespace mavlink
