#ifndef lib_CAN_Interface_CAN_Interface_hpp
#define lib_CAN_Interface_CAN_Interface_hpp

#include <Notifications.hpp>
#include <Log.hpp>

#include "Packets.hpp"
#include "CAN_Frame.hpp"

#ifndef UNIT_TEST
#include <mcp2515_can.h>
#else
#include <CAN_Mock.hpp>
#endif

class CAN_Interface
{
#ifndef UNIT_TEST
    mcp2515_can CAN;
#else
    CAN_Mock CAN;
#endif

    /// echo request frame model to be subscribed to
    Subject<Echo_Request_Packet> latest_echo_request_frame;
    /// echo response frame model to be subscribed to
    Subject<Echo_Response_Packet> latest_echo_response_frame;

public:
    /**
     * Constructor. Assigns the CS pin for the CAN module
     */
    CAN_Interface();

    /**
     * Initialise the connected CAN module
     * @return true on success, false otherwise
     */
    bool init();

    /**
     * Send a frame across the CAN bus
     * @param frame - Frame to send 
     * @return true on success, false otherwise
     */
    bool send(CAN_Frame frame);

    /**
     * Read the latest message from the CAN bus. This should be called regularly
     */
    void read_latest_message();

    /**
     * Checks if a message is waiting for us to read it
     * @return true if message is available, false otherwise
     */
    bool message_available();

    /**
     * Get the 'echo request' model for observers to subscribe to
     * @return the Echo_Request_Packet subject
     */
    Subject<Echo_Request_Packet> *get_request_packet_model();

    /**
     * Get the 'echo response' model for observers to subscribe to
     * @return the Echo_Response_Packet subject
     */
    Subject<Echo_Response_Packet> *get_response_packet_model();

private:
    /**
     * Parse a packet into its specialised packet (e.g. echo_request_packet) and assign it to a subject to notify relevant subscribers
     * @return true if packet parsed successfully, false otherwise
     */
    bool parse_and_update();
};

#endif /* lib_CAN_Interface_CAN_Interface_hpp */