/** @file
 *	@brief MAVLink comm testsuite protocol generated from python_array_test.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "python_array_test.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(python_array_test, ARRAY_TEST_0)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::python_array_test::msg::ARRAY_TEST_0 packet_in{};
    packet_in.v1 = 77;
    packet_in.ar_i8 = {{ -112, -111, -110, -109 }};
    packet_in.ar_u8 = {{ 156, 157, 158, 159 }};
    packet_in.ar_u16 = {{ 18067, 18068, 18069, 18070 }};
    packet_in.ar_u32 = {{ 963497464, 963497465, 963497466, 963497467 }};

    mavlink::python_array_test::msg::ARRAY_TEST_0 packet1{};
    mavlink::python_array_test::msg::ARRAY_TEST_0 packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.v1, packet2.v1);
    EXPECT_EQ(packet1.ar_i8, packet2.ar_i8);
    EXPECT_EQ(packet1.ar_u8, packet2.ar_u8);
    EXPECT_EQ(packet1.ar_u16, packet2.ar_u16);
    EXPECT_EQ(packet1.ar_u32, packet2.ar_u32);
}

#ifdef TEST_INTEROP
TEST(python_array_test_interop, ARRAY_TEST_0)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_array_test_0_t packet_c {
         { 963497464, 963497465, 963497466, 963497467 }, { 18067, 18068, 18069, 18070 }, 77, { -112, -111, -110, -109 }, { 156, 157, 158, 159 }
    };

    mavlink::python_array_test::msg::ARRAY_TEST_0 packet_in{};
    packet_in.v1 = 77;
    packet_in.ar_i8 = {{ -112, -111, -110, -109 }};
    packet_in.ar_u8 = {{ 156, 157, 158, 159 }};
    packet_in.ar_u16 = {{ 18067, 18068, 18069, 18070 }};
    packet_in.ar_u32 = {{ 963497464, 963497465, 963497466, 963497467 }};

    mavlink::python_array_test::msg::ARRAY_TEST_0 packet2{};

    mavlink_msg_array_test_0_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.v1, packet2.v1);
    EXPECT_EQ(packet_in.ar_i8, packet2.ar_i8);
    EXPECT_EQ(packet_in.ar_u8, packet2.ar_u8);
    EXPECT_EQ(packet_in.ar_u16, packet2.ar_u16);
    EXPECT_EQ(packet_in.ar_u32, packet2.ar_u32);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(python_array_test, ARRAY_TEST_1)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::python_array_test::msg::ARRAY_TEST_1 packet_in{};
    packet_in.ar_u32 = {{ 963497464, 963497465, 963497466, 963497467 }};

    mavlink::python_array_test::msg::ARRAY_TEST_1 packet1{};
    mavlink::python_array_test::msg::ARRAY_TEST_1 packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.ar_u32, packet2.ar_u32);
}

#ifdef TEST_INTEROP
TEST(python_array_test_interop, ARRAY_TEST_1)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_array_test_1_t packet_c {
         { 963497464, 963497465, 963497466, 963497467 }
    };

    mavlink::python_array_test::msg::ARRAY_TEST_1 packet_in{};
    packet_in.ar_u32 = {{ 963497464, 963497465, 963497466, 963497467 }};

    mavlink::python_array_test::msg::ARRAY_TEST_1 packet2{};

    mavlink_msg_array_test_1_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.ar_u32, packet2.ar_u32);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(python_array_test, ARRAY_TEST_3)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::python_array_test::msg::ARRAY_TEST_3 packet_in{};
    packet_in.v = 53;
    packet_in.ar_u32 = {{ 963497464, 963497465, 963497466, 963497467 }};

    mavlink::python_array_test::msg::ARRAY_TEST_3 packet1{};
    mavlink::python_array_test::msg::ARRAY_TEST_3 packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.v, packet2.v);
    EXPECT_EQ(packet1.ar_u32, packet2.ar_u32);
}

#ifdef TEST_INTEROP
TEST(python_array_test_interop, ARRAY_TEST_3)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_array_test_3_t packet_c {
         { 963497464, 963497465, 963497466, 963497467 }, 53
    };

    mavlink::python_array_test::msg::ARRAY_TEST_3 packet_in{};
    packet_in.v = 53;
    packet_in.ar_u32 = {{ 963497464, 963497465, 963497466, 963497467 }};

    mavlink::python_array_test::msg::ARRAY_TEST_3 packet2{};

    mavlink_msg_array_test_3_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.v, packet2.v);
    EXPECT_EQ(packet_in.ar_u32, packet2.ar_u32);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(python_array_test, ARRAY_TEST_4)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::python_array_test::msg::ARRAY_TEST_4 packet_in{};
    packet_in.ar_u32 = {{ 963497464, 963497465, 963497466, 963497467 }};
    packet_in.v = 53;

    mavlink::python_array_test::msg::ARRAY_TEST_4 packet1{};
    mavlink::python_array_test::msg::ARRAY_TEST_4 packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.ar_u32, packet2.ar_u32);
    EXPECT_EQ(packet1.v, packet2.v);
}

#ifdef TEST_INTEROP
TEST(python_array_test_interop, ARRAY_TEST_4)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_array_test_4_t packet_c {
         { 963497464, 963497465, 963497466, 963497467 }, 53
    };

    mavlink::python_array_test::msg::ARRAY_TEST_4 packet_in{};
    packet_in.ar_u32 = {{ 963497464, 963497465, 963497466, 963497467 }};
    packet_in.v = 53;

    mavlink::python_array_test::msg::ARRAY_TEST_4 packet2{};

    mavlink_msg_array_test_4_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.ar_u32, packet2.ar_u32);
    EXPECT_EQ(packet_in.v, packet2.v);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(python_array_test, ARRAY_TEST_5)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::python_array_test::msg::ARRAY_TEST_5 packet_in{};
    packet_in.c1 = to_char_array("ABCD");
    packet_in.c2 = to_char_array("FGHI");

    mavlink::python_array_test::msg::ARRAY_TEST_5 packet1{};
    mavlink::python_array_test::msg::ARRAY_TEST_5 packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.c1, packet2.c1);
    EXPECT_EQ(packet1.c2, packet2.c2);
}

#ifdef TEST_INTEROP
TEST(python_array_test_interop, ARRAY_TEST_5)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_array_test_5_t packet_c {
         "ABCD", "FGHI"
    };

    mavlink::python_array_test::msg::ARRAY_TEST_5 packet_in{};
    packet_in.c1 = to_char_array("ABCD");
    packet_in.c2 = to_char_array("FGHI");

    mavlink::python_array_test::msg::ARRAY_TEST_5 packet2{};

    mavlink_msg_array_test_5_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.c1, packet2.c1);
    EXPECT_EQ(packet_in.c2, packet2.c2);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(python_array_test, ARRAY_TEST_6)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::python_array_test::msg::ARRAY_TEST_6 packet_in{};
    packet_in.v1 = 39;
    packet_in.v2 = 19523;
    packet_in.v3 = 963498296;
    packet_in.ar_u32 = {{ 963498504, 963498505 }};
    packet_in.ar_i32 = {{ 963498920, 963498921 }};
    packet_in.ar_u16 = {{ 19627, 19628 }};
    packet_in.ar_i16 = {{ 19835, 19836 }};
    packet_in.ar_u8 = {{ 106, 107 }};
    packet_in.ar_i8 = {{ -16, -15 }};
    packet_in.ar_c = to_char_array("HIJKLMNOPQRSTUVWXYZABCDEFGHIJKL");
    packet_in.ar_d = {{ 123.0, 124.0 }};
    packet_in.ar_f = {{ 269.0, 270.0 }};

    mavlink::python_array_test::msg::ARRAY_TEST_6 packet1{};
    mavlink::python_array_test::msg::ARRAY_TEST_6 packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.v1, packet2.v1);
    EXPECT_EQ(packet1.v2, packet2.v2);
    EXPECT_EQ(packet1.v3, packet2.v3);
    EXPECT_EQ(packet1.ar_u32, packet2.ar_u32);
    EXPECT_EQ(packet1.ar_i32, packet2.ar_i32);
    EXPECT_EQ(packet1.ar_u16, packet2.ar_u16);
    EXPECT_EQ(packet1.ar_i16, packet2.ar_i16);
    EXPECT_EQ(packet1.ar_u8, packet2.ar_u8);
    EXPECT_EQ(packet1.ar_i8, packet2.ar_i8);
    EXPECT_EQ(packet1.ar_c, packet2.ar_c);
    EXPECT_EQ(packet1.ar_d, packet2.ar_d);
    EXPECT_EQ(packet1.ar_f, packet2.ar_f);
}

#ifdef TEST_INTEROP
TEST(python_array_test_interop, ARRAY_TEST_6)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_array_test_6_t packet_c {
         { 123.0, 124.0 }, 963498296, { 963498504, 963498505 }, { 963498920, 963498921 }, { 269.0, 270.0 }, 19523, { 19627, 19628 }, { 19835, 19836 }, 39, { 106, 107 }, { -16, -15 }, "HIJKLMNOPQRSTUVWXYZABCDEFGHIJKL"
    };

    mavlink::python_array_test::msg::ARRAY_TEST_6 packet_in{};
    packet_in.v1 = 39;
    packet_in.v2 = 19523;
    packet_in.v3 = 963498296;
    packet_in.ar_u32 = {{ 963498504, 963498505 }};
    packet_in.ar_i32 = {{ 963498920, 963498921 }};
    packet_in.ar_u16 = {{ 19627, 19628 }};
    packet_in.ar_i16 = {{ 19835, 19836 }};
    packet_in.ar_u8 = {{ 106, 107 }};
    packet_in.ar_i8 = {{ -16, -15 }};
    packet_in.ar_c = to_char_array("HIJKLMNOPQRSTUVWXYZABCDEFGHIJKL");
    packet_in.ar_d = {{ 123.0, 124.0 }};
    packet_in.ar_f = {{ 269.0, 270.0 }};

    mavlink::python_array_test::msg::ARRAY_TEST_6 packet2{};

    mavlink_msg_array_test_6_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.v1, packet2.v1);
    EXPECT_EQ(packet_in.v2, packet2.v2);
    EXPECT_EQ(packet_in.v3, packet2.v3);
    EXPECT_EQ(packet_in.ar_u32, packet2.ar_u32);
    EXPECT_EQ(packet_in.ar_i32, packet2.ar_i32);
    EXPECT_EQ(packet_in.ar_u16, packet2.ar_u16);
    EXPECT_EQ(packet_in.ar_i16, packet2.ar_i16);
    EXPECT_EQ(packet_in.ar_u8, packet2.ar_u8);
    EXPECT_EQ(packet_in.ar_i8, packet2.ar_i8);
    EXPECT_EQ(packet_in.ar_c, packet2.ar_c);
    EXPECT_EQ(packet_in.ar_d, packet2.ar_d);
    EXPECT_EQ(packet_in.ar_f, packet2.ar_f);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(python_array_test, ARRAY_TEST_7)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::python_array_test::msg::ARRAY_TEST_7 packet_in{};
    packet_in.ar_d = {{ 123.0, 124.0 }};
    packet_in.ar_f = {{ 129.0, 130.0 }};
    packet_in.ar_u32 = {{ 963498712, 963498713 }};
    packet_in.ar_i32 = {{ 963499128, 963499129 }};
    packet_in.ar_u16 = {{ 19315, 19316 }};
    packet_in.ar_i16 = {{ 19523, 19524 }};
    packet_in.ar_u8 = {{ 149, 150 }};
    packet_in.ar_i8 = {{ 27, 28 }};
    packet_in.ar_c = to_char_array("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDE");

    mavlink::python_array_test::msg::ARRAY_TEST_7 packet1{};
    mavlink::python_array_test::msg::ARRAY_TEST_7 packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.ar_d, packet2.ar_d);
    EXPECT_EQ(packet1.ar_f, packet2.ar_f);
    EXPECT_EQ(packet1.ar_u32, packet2.ar_u32);
    EXPECT_EQ(packet1.ar_i32, packet2.ar_i32);
    EXPECT_EQ(packet1.ar_u16, packet2.ar_u16);
    EXPECT_EQ(packet1.ar_i16, packet2.ar_i16);
    EXPECT_EQ(packet1.ar_u8, packet2.ar_u8);
    EXPECT_EQ(packet1.ar_i8, packet2.ar_i8);
    EXPECT_EQ(packet1.ar_c, packet2.ar_c);
}

#ifdef TEST_INTEROP
TEST(python_array_test_interop, ARRAY_TEST_7)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_array_test_7_t packet_c {
         { 123.0, 124.0 }, { 129.0, 130.0 }, { 963498712, 963498713 }, { 963499128, 963499129 }, { 19315, 19316 }, { 19523, 19524 }, { 149, 150 }, { 27, 28 }, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDE"
    };

    mavlink::python_array_test::msg::ARRAY_TEST_7 packet_in{};
    packet_in.ar_d = {{ 123.0, 124.0 }};
    packet_in.ar_f = {{ 129.0, 130.0 }};
    packet_in.ar_u32 = {{ 963498712, 963498713 }};
    packet_in.ar_i32 = {{ 963499128, 963499129 }};
    packet_in.ar_u16 = {{ 19315, 19316 }};
    packet_in.ar_i16 = {{ 19523, 19524 }};
    packet_in.ar_u8 = {{ 149, 150 }};
    packet_in.ar_i8 = {{ 27, 28 }};
    packet_in.ar_c = to_char_array("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDE");

    mavlink::python_array_test::msg::ARRAY_TEST_7 packet2{};

    mavlink_msg_array_test_7_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.ar_d, packet2.ar_d);
    EXPECT_EQ(packet_in.ar_f, packet2.ar_f);
    EXPECT_EQ(packet_in.ar_u32, packet2.ar_u32);
    EXPECT_EQ(packet_in.ar_i32, packet2.ar_i32);
    EXPECT_EQ(packet_in.ar_u16, packet2.ar_u16);
    EXPECT_EQ(packet_in.ar_i16, packet2.ar_i16);
    EXPECT_EQ(packet_in.ar_u8, packet2.ar_u8);
    EXPECT_EQ(packet_in.ar_i8, packet2.ar_i8);
    EXPECT_EQ(packet_in.ar_c, packet2.ar_c);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(python_array_test, ARRAY_TEST_8)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::python_array_test::msg::ARRAY_TEST_8 packet_in{};
    packet_in.v3 = 963498296;
    packet_in.ar_d = {{ 123.0, 124.0 }};
    packet_in.ar_u16 = {{ 18275, 18276 }};

    mavlink::python_array_test::msg::ARRAY_TEST_8 packet1{};
    mavlink::python_array_test::msg::ARRAY_TEST_8 packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.v3, packet2.v3);
    EXPECT_EQ(packet1.ar_d, packet2.ar_d);
    EXPECT_EQ(packet1.ar_u16, packet2.ar_u16);
}

#ifdef TEST_INTEROP
TEST(python_array_test_interop, ARRAY_TEST_8)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_array_test_8_t packet_c {
         { 123.0, 124.0 }, 963498296, { 18275, 18276 }
    };

    mavlink::python_array_test::msg::ARRAY_TEST_8 packet_in{};
    packet_in.v3 = 963498296;
    packet_in.ar_d = {{ 123.0, 124.0 }};
    packet_in.ar_u16 = {{ 18275, 18276 }};

    mavlink::python_array_test::msg::ARRAY_TEST_8 packet2{};

    mavlink_msg_array_test_8_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.v3, packet2.v3);
    EXPECT_EQ(packet_in.ar_d, packet2.ar_d);
    EXPECT_EQ(packet_in.ar_u16, packet2.ar_u16);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
