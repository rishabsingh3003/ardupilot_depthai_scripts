/** @file
 *	@brief MAVLink comm testsuite protocol generated from ualberta.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "ualberta.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(ualberta, NAV_FILTER_BIAS)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::ualberta::msg::NAV_FILTER_BIAS packet_in{};
    packet_in.usec = 93372036854775807ULL;
    packet_in.accel_0 = 73.0;
    packet_in.accel_1 = 101.0;
    packet_in.accel_2 = 129.0;
    packet_in.gyro_0 = 157.0;
    packet_in.gyro_1 = 185.0;
    packet_in.gyro_2 = 213.0;

    mavlink::ualberta::msg::NAV_FILTER_BIAS packet1{};
    mavlink::ualberta::msg::NAV_FILTER_BIAS packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.usec, packet2.usec);
    EXPECT_EQ(packet1.accel_0, packet2.accel_0);
    EXPECT_EQ(packet1.accel_1, packet2.accel_1);
    EXPECT_EQ(packet1.accel_2, packet2.accel_2);
    EXPECT_EQ(packet1.gyro_0, packet2.gyro_0);
    EXPECT_EQ(packet1.gyro_1, packet2.gyro_1);
    EXPECT_EQ(packet1.gyro_2, packet2.gyro_2);
}

#ifdef TEST_INTEROP
TEST(ualberta_interop, NAV_FILTER_BIAS)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_nav_filter_bias_t packet_c {
         93372036854775807ULL, 73.0, 101.0, 129.0, 157.0, 185.0, 213.0
    };

    mavlink::ualberta::msg::NAV_FILTER_BIAS packet_in{};
    packet_in.usec = 93372036854775807ULL;
    packet_in.accel_0 = 73.0;
    packet_in.accel_1 = 101.0;
    packet_in.accel_2 = 129.0;
    packet_in.gyro_0 = 157.0;
    packet_in.gyro_1 = 185.0;
    packet_in.gyro_2 = 213.0;

    mavlink::ualberta::msg::NAV_FILTER_BIAS packet2{};

    mavlink_msg_nav_filter_bias_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.usec, packet2.usec);
    EXPECT_EQ(packet_in.accel_0, packet2.accel_0);
    EXPECT_EQ(packet_in.accel_1, packet2.accel_1);
    EXPECT_EQ(packet_in.accel_2, packet2.accel_2);
    EXPECT_EQ(packet_in.gyro_0, packet2.gyro_0);
    EXPECT_EQ(packet_in.gyro_1, packet2.gyro_1);
    EXPECT_EQ(packet_in.gyro_2, packet2.gyro_2);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(ualberta, RADIO_CALIBRATION)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::ualberta::msg::RADIO_CALIBRATION packet_in{};
    packet_in.aileron = {{ 17235, 17236, 17237 }};
    packet_in.elevator = {{ 17547, 17548, 17549 }};
    packet_in.rudder = {{ 17859, 17860, 17861 }};
    packet_in.gyro = {{ 18171, 18172 }};
    packet_in.pitch = {{ 18379, 18380, 18381, 18382, 18383 }};
    packet_in.throttle = {{ 18899, 18900, 18901, 18902, 18903 }};

    mavlink::ualberta::msg::RADIO_CALIBRATION packet1{};
    mavlink::ualberta::msg::RADIO_CALIBRATION packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.aileron, packet2.aileron);
    EXPECT_EQ(packet1.elevator, packet2.elevator);
    EXPECT_EQ(packet1.rudder, packet2.rudder);
    EXPECT_EQ(packet1.gyro, packet2.gyro);
    EXPECT_EQ(packet1.pitch, packet2.pitch);
    EXPECT_EQ(packet1.throttle, packet2.throttle);
}

#ifdef TEST_INTEROP
TEST(ualberta_interop, RADIO_CALIBRATION)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_radio_calibration_t packet_c {
         { 17235, 17236, 17237 }, { 17547, 17548, 17549 }, { 17859, 17860, 17861 }, { 18171, 18172 }, { 18379, 18380, 18381, 18382, 18383 }, { 18899, 18900, 18901, 18902, 18903 }
    };

    mavlink::ualberta::msg::RADIO_CALIBRATION packet_in{};
    packet_in.aileron = {{ 17235, 17236, 17237 }};
    packet_in.elevator = {{ 17547, 17548, 17549 }};
    packet_in.rudder = {{ 17859, 17860, 17861 }};
    packet_in.gyro = {{ 18171, 18172 }};
    packet_in.pitch = {{ 18379, 18380, 18381, 18382, 18383 }};
    packet_in.throttle = {{ 18899, 18900, 18901, 18902, 18903 }};

    mavlink::ualberta::msg::RADIO_CALIBRATION packet2{};

    mavlink_msg_radio_calibration_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.aileron, packet2.aileron);
    EXPECT_EQ(packet_in.elevator, packet2.elevator);
    EXPECT_EQ(packet_in.rudder, packet2.rudder);
    EXPECT_EQ(packet_in.gyro, packet2.gyro);
    EXPECT_EQ(packet_in.pitch, packet2.pitch);
    EXPECT_EQ(packet_in.throttle, packet2.throttle);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(ualberta, UALBERTA_SYS_STATUS)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::ualberta::msg::UALBERTA_SYS_STATUS packet_in{};
    packet_in.mode = 5;
    packet_in.nav_mode = 72;
    packet_in.pilot = 139;

    mavlink::ualberta::msg::UALBERTA_SYS_STATUS packet1{};
    mavlink::ualberta::msg::UALBERTA_SYS_STATUS packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.mode, packet2.mode);
    EXPECT_EQ(packet1.nav_mode, packet2.nav_mode);
    EXPECT_EQ(packet1.pilot, packet2.pilot);
}

#ifdef TEST_INTEROP
TEST(ualberta_interop, UALBERTA_SYS_STATUS)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_ualberta_sys_status_t packet_c {
         5, 72, 139
    };

    mavlink::ualberta::msg::UALBERTA_SYS_STATUS packet_in{};
    packet_in.mode = 5;
    packet_in.nav_mode = 72;
    packet_in.pilot = 139;

    mavlink::ualberta::msg::UALBERTA_SYS_STATUS packet2{};

    mavlink_msg_ualberta_sys_status_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.mode, packet2.mode);
    EXPECT_EQ(packet_in.nav_mode, packet2.nav_mode);
    EXPECT_EQ(packet_in.pilot, packet2.pilot);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
