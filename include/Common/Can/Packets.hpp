#ifndef COMMON_CAN_PACKETS_HPP
#define COMMON_CAN_PACKETS_HPP

#include <stdint.h>

#define CAN_FRAME_SIZE 8

typedef uint16_t packet_id_t;

// Packet type id definitions
#define CAN_PACKET_HELLO_ID 0
#define CAN_PACKET_WORLD_ID 1

#define CAN_PACKET_TYPE_COUNT 2

namespace Common {
    namespace Can {
        typedef void (*PacketHandler)(packet_id_t id, uint8_t(&serialised_packet_data)[CAN_FRAME_SIZE]);

        /// Interface defining the methods that a serialisable Packet must implement.
        struct PacketBase {
            /// The unique ID for this packet type.
            /// @returns A constant, unique ID
            virtual const packet_id_t id() = 0;

            /// Attempts to serialise the packet instance into the given buffer.
            /// @param buffer The buffer into which the packet's data should be serialised
            /// @returns Whether the serialisation was successful
            virtual const bool try_to_bytes(uint8_t(&buffer)[CAN_FRAME_SIZE]) = 0;

            /// Attempts to deserialise a packet instance from the given buffer,
            /// @param buffer The buffer from which the packet instance should be deserialised
            /// @returns Whether the deserialisation was succcessful
            virtual bool try_from_bytes(uint8_t(&buffer)[CAN_FRAME_SIZE]) = 0;
        };

        struct HelloPacket : public PacketBase {
            virtual const packet_id_t id() { return CAN_PACKET_HELLO_ID; }

            virtual const bool try_serialise(uint8_t(&buffer)[CAN_FRAME_SIZE]) {
                return true;
            }

            virtual bool try_deserialise(uint8_t(&buffer)[CAN_FRAME_SIZE]) {
                return true;
            }
        };

        struct WorldPacket : public PacketBase {
            virtual const packet_id_t id() { return CAN_PACKET_WORLD_ID; }

            virtual const bool try_serialise(uint8_t(&buffer)[CAN_FRAME_SIZE]) {
                return true;
            }

            virtual bool try_deserialise(uint8_t(&buffer)[CAN_FRAME_SIZE]) {
                return true;
            }
        };
    };
};

#endif // COMMON_CAN_PACKETS_HPP