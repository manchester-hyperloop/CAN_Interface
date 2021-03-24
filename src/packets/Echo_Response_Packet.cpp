#include "Packets.hpp"

Echo_Response_Packet::Echo_Response_Packet()
{
    can_id = Packet_Priority::PRIORITY_ECHO_RESPONSE;
}

Echo_Response_Packet Echo_Response_Packet::serialise(uint16_t response_value)
{
    Echo_Response_Packet pkt;

    memcpy(&pkt.data[0], &response_value, sizeof(response_value));
    pkt.can_dlc = sizeof(response_value);

    return pkt;
}

void Echo_Response_Packet::deserialise(uint16_t *buf)
{
    memcpy(buf, &data[0], sizeof(uint16_t));
}
