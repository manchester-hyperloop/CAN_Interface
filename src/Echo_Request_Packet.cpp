#include "Packets.hpp"

/**
 * Basic constructor. Assigns ID to frame
 */
Echo_Request_Packet::Echo_Request_Packet()
{
    can_id = Packet_Priority::PRIORITY_ECHO_REQUEST;
}

/**
 * Create a echo request frame with some arbitrary value.
 * We chose to use a uint16_t, but this value could really be anything!
 * @param random_value some arbitrary value
 */
Echo_Request_Packet Echo_Request_Packet::serialise(uint16_t random_value)
{
    Echo_Request_Packet pkt;

    memcpy(&pkt.data[0], &random_value, sizeof(random_value));
    pkt.can_dlc = sizeof(random_value);

    return pkt;
}

/**
 * Deserialise the frame into a uint16_t passed
 * @param dst - The destination to copy the data from the frame into
 */
void Echo_Request_Packet::deserialise(uint16_t *buf)
{
    memcpy(buf, &data[0], sizeof(uint16_t));
}
