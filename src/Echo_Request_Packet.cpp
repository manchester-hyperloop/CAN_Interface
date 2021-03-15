#include "Packets.hpp"

Echo_Request_Packet::Echo_Request_Packet()
{
    can_id = Packet_Priority::PRIORITY_ECHO_REQUEST;
}

Echo_Request_Packet::Echo_Request_Packet(uint16_t random_value)
{
    can_id = Packet_Priority::PRIORITY_ECHO_REQUEST;
    memcpy(&data[0], &random_value, sizeof(random_value));

    can_dlc = sizeof(random_value);
}

void Echo_Request_Packet::parse_to_core_values(uint16_t *buf)
{
    memcpy(buf, &data[0], sizeof(uint16_t));
}
