//
//  main.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/03/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include <Arduino_Mock.hpp>
#endif

#include <Log.hpp>
#include <CAN_Interface.hpp>
#include <Notifications.hpp>
#include <Callback.hpp>

// #define SENDER

CAN_Interface can_bus;

#ifdef SENDER
void print_echo_response(Echo_Response_Packet pkt)
{
    uint16_t response_value;
    pkt.parse_to_core_values(&response_value);

    LOG("Received response: ", response_value);
}
#else
void respond_to_echo_request(Echo_Request_Packet pkt)
{
    uint16_t response_value;
    pkt.parse_to_core_values(&response_value);

    LOG("Received echo msg: ", response_value);

    Echo_Response_Packet response_pkt(response_value);
    can_bus.send(response_pkt);
}
#endif

void setup()
{
    // Start the serial port
    Serial.begin(115200);

    // Initialise the logger
    log_inst.init();

#ifdef SENDER
    LOG("Starting as SENDER...");
#else
    LOG("Starting as RECEIVER...");
#endif

    // Initialise the can bus
    can_bus.init();
}

void loop()
{
    uint16_t counter = 0;
#ifdef SENDER
    Observer<Echo_Response_Packet> observer(can_bus.get_response_packet_model(), new FuncCallback<Echo_Response_Packet>(&print_echo_response));
#else
    Observer<Echo_Request_Packet> observer(can_bus.get_request_packet_model(), new FuncCallback<Echo_Request_Packet>(&respond_to_echo_request));
#endif

    while (true)
    {

#ifdef SENDER
        LOG("Sending value: ", counter);
        CAN_Frame pkt = Echo_Request_Packet(counter++);

        if (!can_bus.send(pkt))
            LOG_WARN("Message failed to send...");

        while (!can_bus.message_available())
        {
            LOG("Waiting for message...");
            delay(500);
        }

        LOG("Reading latest message");
        can_bus.read_latest_message();

#else
        while (!can_bus.message_available())
        {
            LOG("Waiting for message...");
            delay(500);
        }

        can_bus.read_latest_message();
        delay(500);

        // Notifications will respond to message
#endif
    }
}
