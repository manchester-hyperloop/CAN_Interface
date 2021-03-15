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

    Subject<Echo_Request_Packet> latest_echo_request_frame;
    Subject<Echo_Response_Packet> latest_echo_response_frame;

public:
    CAN_Interface()
        : CAN(10)
    {
    }

    bool init()
    {
        if (CAN.begin(CAN_500KBPS) != CAN_OK)
        {
            LOG_ERR(F("CAN BUS init failed"));
            return false;
        }

        return true;
    }

    bool send(CAN_Frame frame)
    {
        if (CAN.sendMsgBuf(frame.can_id, 0, frame.can_dlc, frame.data) != CAN_OK)
        {
            LOG_WARN(F("Failed to send last CAN message"));
            return false;
        }

        return true;
    }

    void read_latest_message()
    {
        while (message_available())
        {
            parse_and_update();
        }
    }

    bool message_available()
    {
        return CAN_MSGAVAIL == CAN.checkReceive();
    }

    Subject<Echo_Request_Packet> *get_request_packet_model()
    {
        return &latest_echo_request_frame;
    }

    Subject<Echo_Response_Packet> *get_response_packet_model()
    {
        return &latest_echo_response_frame;
    }

private:
    bool parse_and_update()
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
            specialise_abstract_frame(&echo_request_packet, &frame);
            latest_echo_request_frame = echo_request_packet;
            return true;
        }

        case Packet_Priority::PRIORITY_ECHO_RESPONSE:
        {
            Echo_Response_Packet echo_response_packet;
            specialise_abstract_frame(&echo_response_packet, &frame);
            latest_echo_response_frame = echo_response_packet;
            return true;
        }

        default:
            return false;
        }
    }
};

#endif /* lib_CAN_Interface_CAN_Interface_hpp */