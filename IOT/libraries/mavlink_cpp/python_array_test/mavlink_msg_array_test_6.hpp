// MESSAGE ARRAY_TEST_6 support class

#pragma once

namespace mavlink {
namespace python_array_test {
namespace msg {

/**
 * @brief ARRAY_TEST_6 message
 *
 * Array test #6.
 */
struct ARRAY_TEST_6 : mavlink::Message {
    static constexpr msgid_t MSG_ID = 17156;
    static constexpr size_t LENGTH = 91;
    static constexpr size_t MIN_LENGTH = 91;
    static constexpr uint8_t CRC_EXTRA = 14;
    static constexpr auto NAME = "ARRAY_TEST_6";


    uint8_t v1; /*<  Stub field */
    uint16_t v2; /*<  Stub field */
    uint32_t v3; /*<  Stub field */
    std::array<uint32_t, 2> ar_u32; /*<  Value array */
    std::array<int32_t, 2> ar_i32; /*<  Value array */
    std::array<uint16_t, 2> ar_u16; /*<  Value array */
    std::array<int16_t, 2> ar_i16; /*<  Value array */
    std::array<uint8_t, 2> ar_u8; /*<  Value array */
    std::array<int8_t, 2> ar_i8; /*<  Value array */
    std::array<char, 32> ar_c; /*<  Value array */
    std::array<double, 2> ar_d; /*<  Value array */
    std::array<float, 2> ar_f; /*<  Value array */


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
        ss << "  v2: " << v2 << std::endl;
        ss << "  v3: " << v3 << std::endl;
        ss << "  ar_u32: [" << to_string(ar_u32) << "]" << std::endl;
        ss << "  ar_i32: [" << to_string(ar_i32) << "]" << std::endl;
        ss << "  ar_u16: [" << to_string(ar_u16) << "]" << std::endl;
        ss << "  ar_i16: [" << to_string(ar_i16) << "]" << std::endl;
        ss << "  ar_u8: [" << to_string(ar_u8) << "]" << std::endl;
        ss << "  ar_i8: [" << to_string(ar_i8) << "]" << std::endl;
        ss << "  ar_c: \"" << to_string(ar_c) << "\"" << std::endl;
        ss << "  ar_d: [" << to_string(ar_d) << "]" << std::endl;
        ss << "  ar_f: [" << to_string(ar_f) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << ar_d;                          // offset: 0
        map << v3;                            // offset: 16
        map << ar_u32;                        // offset: 20
        map << ar_i32;                        // offset: 28
        map << ar_f;                          // offset: 36
        map << v2;                            // offset: 44
        map << ar_u16;                        // offset: 46
        map << ar_i16;                        // offset: 50
        map << v1;                            // offset: 54
        map << ar_u8;                         // offset: 55
        map << ar_i8;                         // offset: 57
        map << ar_c;                          // offset: 59
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> ar_d;                          // offset: 0
        map >> v3;                            // offset: 16
        map >> ar_u32;                        // offset: 20
        map >> ar_i32;                        // offset: 28
        map >> ar_f;                          // offset: 36
        map >> v2;                            // offset: 44
        map >> ar_u16;                        // offset: 46
        map >> ar_i16;                        // offset: 50
        map >> v1;                            // offset: 54
        map >> ar_u8;                         // offset: 55
        map >> ar_i8;                         // offset: 57
        map >> ar_c;                          // offset: 59
    }
};

} // namespace msg
} // namespace python_array_test
} // namespace mavlink
