//
//  Packets.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 14/03/2021.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef lib_CAN_Interface_Packets_hpp
#define lib_CAN_Interface_Packets_hpp

#ifndef UNIT_TEST
#include <mcp2515.h>
#else
#include <MCP2515_Mock.hpp>
#endif

/**
 * Copy core information from one frame to another. Useful in copying data to a 'specialised' frame.
 * @param dst - Destination frame
 * @param src - Source frame
 */
void copy_frame(can_frame *dst, can_frame *src);

/**
 * The priority of a given packet.
 * The closer the value is to zero, the higher the priority of the related 
 * packet; it will be handled by a node before a lower priority packet is sent.
 */
enum Packet_Priority
{
    CAN_PRIORITY_ECHO_REQUEST = 0,
    CAN_PRIORITY_ECHO_RESPONSE = 1,
    CAN_PRIORITY_SET_BRAKE = 2,
    CAN_PRIORITY_SET_ACCEL = 3,
    CAN_PRIORITY_SET_LIGHT = 4,
};


#ifdef CAN_PACKET_ECHO_REQUEST
/**
 * Requests all connected CAN nodes to respond with the given value.
 */
struct Echo_Request_Packet : public can_frame
{
    /**
     * Basic constructor. Assigns ID to frame
     */
    Echo_Request_Packet();

    /**
     * Create a echo request frame with some arbitrary value.
     * We chose to use a uint16_t, but this value could really be anything!
     * @param random_value some arbitrary value
     */
    static Echo_Request_Packet serialise(uint16_t random_value);

    /**
     * Deserialise the frame into a uint16_t passed
     * @param dst - The destination to copy the data from the frame into
     */
    void deserialise(uint16_t *dst);
};
#endif

#ifdef CAN_PACKET_ECHO_RESPONSE
/**
 * Echoes back the requested value.
 */
struct Echo_Response_Packet : public can_frame
{
    /**
     * Basic constructor. Assigns ID to frame
     */
    Echo_Response_Packet();

    /**
     * Create a echo response frame with some arbitrary value.
     * We chose to use a uint16_t, but this value could really be anything!
     * The value that we load into this frame should be the one sent to us by the echo request frame
     * @param random_value some arbitrary value
     */
    static Echo_Response_Packet serialise(uint16_t random_value);

    /**
     * Deserialise the frame into a uint16_t passed
     * @param dst The destination to copy the data from the frame into
     */
    void deserialise(uint16_t *dst);
};
#endif

#ifdef CAN_PACKET_SET_BRAKE

struct Set_Brake_Packet : public can_frame
{
    /**
     * Basic constructor. Assigns ID to frame
     */
    Echo_Response_Packet();

    /**
     * Create a echo response frame with some arbitrary value.
     * We chose to use a uint16_t, but this value could really be anything!
     * The value that we load into this frame should be the one sent to us by the echo request frame
     * @param random_value some arbitrary value
     */
    static Set_Brake_Packet serialise(uint16_t random_value);

    /**
     * Deserialise the frame into a uint16_t passed
     * @param dst The destination to copy the data from the frame into
     */
    void deserialise(uint16_t *dst);
}

#endif

#ifdef CAN_PACKET_SET_ACCEL

struct Set_Accel_Packet : public can_frame
{
    /**
     * Basic constructor. Assigns ID to frame
     */
    Echo_Response_Packet();

    /**
     * Create a echo response frame with some arbitrary value.
     * We chose to use a uint16_t, but this value could really be anything!
     * The value that we load into this frame should be the one sent to us by the echo request frame
     * @param random_value some arbitrary value
     */
    static Set_Accel_Packet serialise(uint16_t random_value);

    /**
     * Deserialise the frame into a uint16_t passed
     * @param dst The destination to copy the data from the frame into
     */
    void deserialise(uint16_t *dst);
}

#endif

#ifdef CAN_PACKET_SET_LIGHT

struct Set_Light_Packet : public can_frame
{
 /**
     * Basic constructor. Assigns ID to frame
     */
    Set_Light_Packet();

    /**
     * Create a echo response frame with some arbitrary value.
     * We chose to use a uint16_t, but this value could really be anything!
     * The value that we load into this frame should be the one sent to us by the echo request frame
     * @param random_value some arbitrary value
     */
    static Set_Light_Packet serialise(uint16_t random_value);

    /**
     * Deserialise the frame into a uint16_t passed
     * @param dst The destination to copy the data from the frame into
     */
    void deserialise(uint16_t *dst);
}

#endif

#endif /* lib_CAN_Interface_Packets_hpp */