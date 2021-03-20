//
//  Mode_Test.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#include <unity.h>
#include <CAN_Interface.hpp>
#include <Notifications.hpp>
#include <CAN_Mock.hpp>
#include <Log.hpp>
#include <string.h>

CAN_Interface *interface = nullptr;

void setup(void)
{
    interface = new CAN_Interface();
    interface->init();

    CAN_Mock::message_available = true;
}

void teardown(void)
{
    if (interface != nullptr)
    {
        delete interface;
    }

    interface = nullptr;
}

// Get the log policy from the log instance
File &getLogFileMock()
{
    Log_File_Interface *policy = log_inst.getActiveLogInterface();
    TEST_ASSERT(policy);

    return policy->getLogFile();
}

std::string getLastLoggedMessage()
{
    return getLogFileMock().getLastMessage();
}

// data from an abstract CAN_Frame can be copied to another
void test_copy_frame(void)
{
    CAN_Frame f1, f2;
    f1.can_id = 13;
    f1.can_dlc = 3;

    uint8_t test_data[3] = {1, 2, 3};
    memcpy(f1.data, test_data, 3);

    copy_frame(&f1, &f2);

    TEST_ASSERT_EQUAL(f1.can_id, f2.can_id);
    TEST_ASSERT_EQUAL(f1.can_dlc, f2.can_dlc);

    TEST_ASSERT_EQUAL(f1.data[0], f2.data[0]);
    TEST_ASSERT_EQUAL(f1.data[1], f2.data[1]);
    TEST_ASSERT_EQUAL(f1.data[2], f2.data[2]);
}

// Messages are able to be sent
void test_message_send_possible(void)
{
    setup();

    uint16_t test_data = 11;
    Echo_Response_Packet pkt = Echo_Response_Packet::serialise(test_data);

    bool result = interface->send(pkt);
    TEST_ASSERT(result);

    Echo_Response_Packet tx_packet;
    copy_frame(&tx_packet, &CAN_Mock::latest_tx_frame);

    uint16_t sent_value;
    tx_packet.deserialise(&sent_value);
    TEST_ASSERT_EQUAL(test_data, sent_value);
}

// Warning will be logged if CAN did NOT initialise properly
void test_log_warning_on_unsuccessful_init(void)
{
    CAN_Mock::mayInitialise = false;

    interface = new CAN_Interface();
    interface->init();

    TEST_ASSERT(getLastLoggedMessage().find("ERROR") != std::string::npos);

    CAN_Mock::mayInitialise = true;
}

// Error will be logged if message did NOT send successfully
void test_log_warning_on_unsuccessful_message_send(void)
{
    CAN_Mock::may_send_message = false;

    setup();

    uint16_t test_data = 11;
    CAN_Interface interface;
    Echo_Response_Packet pkt = Echo_Response_Packet::serialise(test_data);

    bool result = interface.send(pkt);
    TEST_ASSERT_FALSE(result);

    // Check message logged successfully
    TEST_ASSERT(getLastLoggedMessage().find("WARNING") != std::string::npos);

    CAN_Mock::may_send_message = true;
}

int main(int argc, char **argv)
{

    UNITY_BEGIN();

    log_inst.init();

    RUN_TEST(test_copy_frame);

    RUN_TEST(test_message_send_possible);
    RUN_TEST(test_log_warning_on_unsuccessful_message_send);
    RUN_TEST(test_log_warning_on_unsuccessful_init);

    UNITY_END();
    return 0;
}