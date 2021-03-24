#include "CAN_Interface.hpp"

CAN_Interface::CAN_Interface(uint8_t CS_pin)
    : CAN(CS_pin)
{
}

bool CAN_Interface::init(CAN_SPEED bit_rate, CAN_CLOCK clock_speed)
{
    // Reset the CAN controller
    if (CAN.reset() != MCP2515::ERROR_OK)
    {
        LOG_ERR(F("CAN BUS failed to init"));
        return false;
    }

    // Set to normal mode
    if (CAN.setNormalMode() != MCP2515::ERROR_OK)
    {
        LOG_ERR(F("Failed to set CAN controller to 'normal' mode"));
        return false;
    }

    // Set bitrate to
    if (CAN.setBitrate(bit_rate, clock_speed) != MCP2515::ERROR_OK)
    {
        LOG_ERR(F("Failed to set bitrate and/or clock speed for CAN controller"));
        return false;
    }

    return true;
}

bool CAN_Interface::send(can_frame *frame)
{
    if (CAN.sendMessage(frame) != MCP2515::ERROR_OK)
    {
        LOG_WARN(F("Failed to send last CAN message"));
        return false;
    }

    return true;
}

void CAN_Interface::read_latest_message()
{
    can_frame latest_frame;
    while (CAN.readMessage(&latest_frame) == MCP2515::ERROR_OK)
    {
        parse_and_update(&latest_frame);
    }
}

bool CAN_Interface::parse_and_update(can_frame *frame)
{
    // Specialise packet and inform subscribers
    switch (frame->can_id)
    {
#ifdef CAN_PACKET_ECHO_REQUEST
    case Packet_Priority::PRIORITY_ECHO_REQUEST:
    {
        Echo_Request_Packet echo_request_packet;
        copy_frame(&echo_request_packet, frame);
        latest_echo_request_frame = echo_request_packet;
        return true;
    }
#endif

#ifdef CAN_PACKET_ECHO_RESPONSE
    case Packet_Priority::PRIORITY_ECHO_RESPONSE:
    {
        Echo_Response_Packet echo_response_packet;
        copy_frame(&echo_response_packet, frame);
        latest_echo_response_frame = echo_response_packet;
        return true;
    }
#endif

    default:
        LOG_WARN("Packet with id ", frame->can_id, " and length ", frame->can_dlc, "not recognised!");
        return false;
    }
}