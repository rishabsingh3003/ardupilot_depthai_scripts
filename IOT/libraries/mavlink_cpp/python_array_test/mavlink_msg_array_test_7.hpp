// MESSAGE ARRAY_TEST_7 support class

#pragma once

namespace mavlink {
namespace python_array_test {
namespace msg {

/**
 * @brief ARRAY_TEST_7 message
 *
 * Array test #7.
 */
struct ARRAY_TEST_7 : mavlink::Message {
    static constexpr msgid_t MSG_ID = 17157;
    static constexpr size_t LENGTH = 84;
    static constexpr size_t MIN_LENGTH = 84;
    static constexpr uint8_t CRC_EXTRA = 187;
    static constexpr auto NAME = "ARRAY_TEST_7";


    std::array<double, 2> ar_d; /*<  Value array */
    std::array<float, 2> ar_f; /*<  Value array */
    std::array<uint32_t, 2> ar_u32; /*<  Value array */
    std::array<int32_t, 2> ar_i32; /*<  Value array */
    std::array<uint16_t, 2> ar_u16; /*<  Value array */
    std::array<int16_t, 2> ar_i16; /*<  Value array */
    std::array<uint8_t, 2> ar_u8; /*<  Value array */
    std::array<int8_t, 2> ar_i8; /*<  Value array */
    std::array<char, 32> ar_c; /*<  Value array */


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
        ss << "  ar_d: [" << to_string(ar_d) << "]" << std::endl;
        ss << "  ar_f: [" << to_string(ar_f) << "]" << std::endl;
        ss << "  ar_u32: [" << to_string(ar_u32) << "]" << std::endl;
        ss << "  ar_i32: [" << to_string(ar_i32) << "]" << std::endl;
        ss << "  ar_u16: [" << to_string(ar_u16) << "]" << std::endl;
        ss << "  ar_i16: [" << to_string(ar_i16) << "]" << std::endl;
        ss << "  ar_u8: [" << to_string(ar_u8) << "]" << std::endl;
        ss << "  ar_i8: [" << to_string(ar_i8) << "]" << std::endl;
        ss << "  ar_c: \"" << to_string(ar_c) << "\"" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << ar_d;                          // offset: 0
        map << ar_f;                          // offset: 16
        map << ar_u32;                        // offset: 24
        map << ar_i32;                        // offset: 32
        map << ar_u16;                        // offset: 40
        map << ar_i16;                        // offset: 44
        map << ar_u8;                         // offset: 48
        map << ar_i8;                         // offset: 50
        map << ar_c;                          // offset: 52
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> ar_d;                          // offset: 0
        map >> ar_f;                          // offset: 16
        map >> ar_u32;                        // offset: 24
        map >> ar_i32;                        // offset: 32
        map >> ar_u16;                        // offset: 40
        map >> ar_i16;                        // offset: 44
        map >> ar_u8;                         // offset: 48
        map >> ar_i8;                         // offset: 50
        map >> ar_c;                          // offset: 52
    }
};

} // namespace msg
} // namespace python_array_test
} // namespace mavlink
