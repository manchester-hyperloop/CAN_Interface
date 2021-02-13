#include "Common/Can/Can.hpp"

using namespace Common::Can;

bool Node::try_write_packet(PacketBase *packet)
{
    if (packet)
    {
        bool success = packet->try_to_bytes(Node::packet_buffer);

        return true;
    }

    return false;
}

bool Node::try_set_packet_handler(const packet_id_t id, const PacketHandler new_handler)
{
    if (id > CAN_PACKET_TYPE_COUNT)
        return false;

    Node::packet_handler_map[id] = new_handler;

    return true;
}