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

#include "CAN_Copy_Frame.hpp"

/**
 * The priority of packets that we can parse. Also used as the ID of a packet. Research how CAN IDs work for more info.
 */
enum Packet_Priority
{
    PRIORITY_ECHO_REQUEST = 0,
    PRIORITY_ECHO_RESPONSE,
};

/**
 * Frame that requests all other devices on the CAN network to echo back a given value
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

/**
 * Frame that responds to an echo request by sending back a given value
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
    static Echo_Response_Packet serialise(uint16_t response_value);

    /**
     * Deserialise the frame into a uint16_t passed
     * @param dst The destination to copy the data from the frame into
     */
    void deserialise(uint16_t *dst);
};

#endif /* lib_CAN_Interface_Packets_hpp */