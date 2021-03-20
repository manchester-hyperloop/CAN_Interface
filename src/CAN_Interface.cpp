#include "CAN_Interface.hpp"

/**
 * Constructor. Assigns the CS pin for the CAN module
 */
CAN_Interface::CAN_Interface()
    : CAN(10)
{
}

/**
 * Initialise the connected CAN module
 * @return true on success, false otherwise
 */
bool CAN_Interface::init()
{
    if (CAN.begin(CAN_500KBPS) != CAN_OK)
    {
        LOG_ERR(F("CAN BUS init failed"));
        return false;
    }

    return true;
}

/**
 * Send a frame across the CAN bus
 * @param frame - Frame to send 
 * @return true on success, false otherwise
 */
bool CAN_Interface::send(CAN_Frame frame)
{
    if (CAN.sendMsgBuf(frame.can_id, 0, frame.can_dlc, frame.data) != CAN_OK)
    {
        LOG_WARN(F("Failed to send last CAN message"));
        return false;
    }

    return true;
}

/**
 * Read the latest message from the CAN bus. This should be called regularly
 */
void CAN_Interface::read_latest_message()
{
    while (message_available())
    {
        parse_and_update();
    }
}

/**
 * Checks if a message is waiting for us to read it
 * @return true if message is available, false otherwise
 */
bool CAN_Interface::message_available()
{
    return CAN_MSGAVAIL == CAN.checkReceive();
}

/**
 * Get the 'echo request' model for observers to subscribe to
 * @return the Echo_Request_Packet subject
 */
Subject<Echo_Request_Packet> *CAN_Interface::get_request_packet_model()
{
    return &latest_echo_request_frame;
}

/**
 * Get the 'echo response' model for observers to subscribe to
 * @return the Echo_Response_Packet subject
 */
Subject<Echo_Response_Packet> *CAN_Interface::get_response_packet_model()
{
    return &latest_echo_response_frame;
}

/**
 * Parse a packet into its specialised packet (e.g. echo_request_packet) and assign it to a subject to notify relevant subscribers
 * @return true if packet parsed successfully, false otherwise
 */
bool CAN_Interface::parse_and_update()
{
    // Read in data
    Echo_Request_Packet frame;
    CAN.readMsgBuf(&frame.can_dlc, &frame.data[0]);
    frame.can_id = CAN.getCanId();

    Packet_Priority priority = (Packet_Priority)frame.can_id;

    // Specialise packet and inform subscribers
    switch (priority)
    {
    case Packet_Priority::PRIORITY_ECHO_REQUEST:
    {
        Echo_Request_Packet echo_request_packet;
        copy_frame(&echo_request_packet, &frame);
        latest_echo_request_frame = echo_request_packet;
        return true;
    }

    case Packet_Priority::PRIORITY_ECHO_RESPONSE:
    {
        Echo_Response_Packet echo_response_packet;
        copy_frame(&echo_response_packet, &frame);
        latest_echo_response_frame = echo_response_packet;
        return true;
    }

    default:
        LOG_WARN("Packet with id ", frame.can_id, " and length ", frame.can_dlc, "not recognised!");
        return false;
    }
}