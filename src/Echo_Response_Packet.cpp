#include "Packets.hpp"

Echo_Response_Packet::Echo_Response_Packet()
{
    can_id = Packet_Priority::PRIORITY_ECHO_RESPONSE;
}

Echo_Response_Packet::Echo_Response_Packet(uint16_t response_value)
{
    can_id = Packet_Priority::PRIORITY_ECHO_RESPONSE;
    memcpy(&data[0], &response_value, sizeof(response_value));

    can_dlc = sizeof(response_value);
}

void Echo_Response_Packet::parse_to_core_values(uint16_t *buf)
{
    memcpy(buf, &data[0], sizeof(uint16_t));
}