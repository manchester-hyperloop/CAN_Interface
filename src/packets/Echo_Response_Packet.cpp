#include "Packets.hpp"

Echo_Response_Packet::Echo_Response_Packet()
{
    can_id = Packet_Priority::PRIORITY_ECHO_RESPONSE;
}

/**
 * Create a echo response frame with some arbitrary value.
 * We chose to use a uint16_t, but this value could really be anything!
 * The value that we load into this frame should be the one sent to us by the echo request frame
 * @param random_value some arbitrary value
 */
Echo_Response_Packet Echo_Response_Packet::serialise(uint16_t response_value)
{
    Echo_Response_Packet pkt;

    memcpy(&pkt.data[0], &response_value, sizeof(response_value));
    pkt.can_dlc = sizeof(response_value);

    return pkt;
}

/**
 * Deserialise the frame into a uint16_t passed
 * @param dst The destination to copy the data from the frame into
 */
void Echo_Response_Packet::deserialise(uint16_t *buf)
{
    memcpy(buf, &data[0], sizeof(uint16_t));
}
