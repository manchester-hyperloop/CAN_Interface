#ifndef COMMON_CAN_CAN_HPP
#define COMMON_CAN_CAN_HPP

/**
 * Addresses for devices connected to the CAN bus
 */
#define TEENSY_CAN_ADDR 0x012

#include "Packets.hpp"

namespace Common {
    namespace Can {
        /// Singleton CAN node instance.
        namespace Node {
            namespace {
                PacketHandler packet_handler_map[CAN_PACKET_TYPE_COUNT];
                uint8_t packet_buffer[8];
            }

            bool try_write_packet(PacketBase *packet);
            bool try_set_packet_handler(const packet_id_t id, const PacketHandler new_handler);
        };
    };
};


#endif /* COMMON_CAN_CAN_HPP */
