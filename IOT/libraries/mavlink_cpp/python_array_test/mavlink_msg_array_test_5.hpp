// MESSAGE ARRAY_TEST_5 support class

#pragma once

namespace mavlink {
namespace python_array_test {
namespace msg {

/**
 * @brief ARRAY_TEST_5 message
 *
 * Array test #5.
 */
struct ARRAY_TEST_5 : mavlink::Message {
    static constexpr msgid_t MSG_ID = 17155;
    static constexpr size_t LENGTH = 10;
    static constexpr size_t MIN_LENGTH = 10;
    static constexpr uint8_t CRC_EXTRA = 27;
    static constexpr auto NAME = "ARRAY_TEST_5";


    std::array<char, 5> c1; /*<  Value array */
    std::array<char, 5> c2; /*<  Value array */


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
        ss << "  c1: \"" << to_string(c1) << "\"" << std::endl;
        ss << "  c2: \"" << to_string(c2) << "\"" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << c1;                            // offset: 0
        map << c2;                            // offset: 5
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> c1;                            // offset: 0
        map >> c2;                            // offset: 5
    }
};

} // namespace msg
} // namespace python_array_test
} // namespace mavlink
