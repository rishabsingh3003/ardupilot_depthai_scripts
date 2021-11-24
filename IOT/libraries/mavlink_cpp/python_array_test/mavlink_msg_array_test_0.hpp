// MESSAGE ARRAY_TEST_0 support class

#pragma once

namespace mavlink {
namespace python_array_test {
namespace msg {

/**
 * @brief ARRAY_TEST_0 message
 *
 * Array test #0.
 */
struct ARRAY_TEST_0 : mavlink::Message {
    static constexpr msgid_t MSG_ID = 17150;
    static constexpr size_t LENGTH = 33;
    static constexpr size_t MIN_LENGTH = 33;
    static constexpr uint8_t CRC_EXTRA = 26;
    static constexpr auto NAME = "ARRAY_TEST_0";


    uint8_t v1; /*<  Stub field */
    std::array<int8_t, 4> ar_i8; /*<  Value array */
    std::array<uint8_t, 4> ar_u8; /*<  Value array */
    std::array<uint16_t, 4> ar_u16; /*<  Value array */
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
        ss << "  v1: " << +v1 << std::endl;
        ss << "  ar_i8: [" << to_string(ar_i8) << "]" << std::endl;
        ss << "  ar_u8: [" << to_string(ar_u8) << "]" << std::endl;
        ss << "  ar_u16: [" << to_string(ar_u16) << "]" << std::endl;
        ss << "  ar_u32: [" << to_string(ar_u32) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << ar_u32;                        // offset: 0
        map << ar_u16;                        // offset: 16
        map << v1;                            // offset: 24
        map << ar_i8;                         // offset: 25
        map << ar_u8;                         // offset: 29
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> ar_u32;                        // offset: 0
        map >> ar_u16;                        // offset: 16
        map >> v1;                            // offset: 24
        map >> ar_i8;                         // offset: 25
        map >> ar_u8;                         // offset: 29
    }
};

} // namespace msg
} // namespace python_array_test
} // namespace mavlink
