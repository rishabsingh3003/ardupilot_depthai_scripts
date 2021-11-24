// MESSAGE ARRAY_TEST_1 support class

#pragma once

namespace mavlink {
namespace python_array_test {
namespace msg {

/**
 * @brief ARRAY_TEST_1 message
 *
 * Array test #1.
 */
struct ARRAY_TEST_1 : mavlink::Message {
    static constexpr msgid_t MSG_ID = 17151;
    static constexpr size_t LENGTH = 16;
    static constexpr size_t MIN_LENGTH = 16;
    static constexpr uint8_t CRC_EXTRA = 72;
    static constexpr auto NAME = "ARRAY_TEST_1";


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
        ss << "  ar_u32: [" << to_string(ar_u32) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << ar_u32;                        // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> ar_u32;                        // offset: 0
    }
};

} // namespace msg
} // namespace python_array_test
} // namespace mavlink
