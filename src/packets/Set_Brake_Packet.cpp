#include "Packets.hpp"

#ifdef CAN_PACKET_SET_BRAKE

Set_Brake_Packet::Echo_Request_Packet()
{
    can_id = Packet_Priority::PRIORITY_ECHO_REQUEST;
}

Set_Brake_Packet Set_Brake_Packet::serialise(uint16_t random_value)
{
    Set_Brake_Packet pkt;

    memcpy(&pkt.data[0], &random_value, sizeof(random_value));
    pkt.can_dlc = sizeof(random_value);

    return pkt;
}

void Set_Brake_Packet::deserialise(uint16_t *buf)
{
    memcpy(buf, &data[0], sizeof(uint16_t));
}

#endif