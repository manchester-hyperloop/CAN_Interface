//
//  Packets.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 14/03/2021.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef lib_CAN_Interface_Packets_hpp
#define lib_CAN_Interface_Packets_hpp

#include "CAN_Frame.hpp"

enum Packet_Priority
{
    PRIORITY_ECHO_REQUEST = 0,
    PRIORITY_ECHO_RESPONSE,
};

struct Echo_Request_Packet : public CAN_Frame
{
    Echo_Request_Packet();

    static Echo_Request_Packet serialise(uint16_t random_value);
    void deserialise(uint16_t *buf);
};

struct Echo_Response_Packet : public CAN_Frame
{
    Echo_Response_Packet();

    static Echo_Response_Packet serialise(uint16_t response_value);
    void deserialise(uint16_t *buf);
};

#endif /* lib_CAN_Interface_Packets_hpp */