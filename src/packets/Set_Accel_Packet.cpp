#include "Packets.hpp"

#ifdef CAN_PACKET_SET_ACCEL

Set_Accel_Packet::Set_Accel_Packet()
{
    can_id = Packet_Priority::CAN_PRIORITY_SET_ACCEL;
}

Set_Accel_Packet Set_Accel_Packet::serialise(uint16_t random_value)
{
    Set_Accel_Packet pkt;

    memcpy(&pkt.data[0], &random_value, sizeof(random_value));
    pkt.can_dlc = sizeof(random_value);

    return pkt;
}

void Set_Accel_Packet::deserialise(uint16_t *buf)
{
    memcpy(buf, &data[0], sizeof(uint16_t));
}

#endif