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
    CAN_Interface();

    bool init();

    bool send(CAN_Frame frame);
    void read_latest_message();
    bool message_available();

    Subject<Echo_Request_Packet> *get_request_packet_model();
    Subject<Echo_Response_Packet> *get_response_packet_model();

private:
    bool parse_and_update();
};

#endif /* lib_CAN_Interface_CAN_Interface_hpp */