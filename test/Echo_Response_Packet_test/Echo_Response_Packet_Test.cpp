#include <cstddef>
#include <unity.h>
#include <CAN_Interface.hpp>
#include <Instance.hpp>
#include <Notifications.hpp>
#include <CAN_Mock.hpp>

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

// TODO: Seperate compilation, parsing and notification into new file for every packet
// Constructor will compile into correct message format
void test_serialise_response_to_correct_packet(void)
{
    uint16_t random_test_value = 13;
    CAN_Frame test_frame = Echo_Response_Packet::serialise(random_test_value);

    // Check that the id is set correctly
    TEST_ASSERT_EQUAL(test_frame.can_id, Packet_Priority::PRIORITY_ECHO_RESPONSE);

    // Check that the data and length of data has been set correctly
    uint16_t compiled_value = 0;
    memcpy(&compiled_value, &test_frame.data, sizeof(compiled_value));
    TEST_ASSERT_EQUAL(compiled_value, random_test_value);
    TEST_ASSERT_EQUAL(test_frame.can_dlc, sizeof(random_test_value));
}

// Parser will parse into correct message type
void test_deserialise_response_to_correct_packet(void)
{
    uint16_t random_test_value = 14;
    Echo_Response_Packet packet = Echo_Response_Packet::serialise(random_test_value);

    uint16_t parsed_value;
    packet.deserialise(&parsed_value);
    TEST_ASSERT_EQUAL(random_test_value, parsed_value);
}

bool response_notification_called = false;
Echo_Response_Packet latest_response_packet;
void get_latest_response_packet(Echo_Response_Packet pkt)
{
    response_notification_called = true;
    latest_response_packet = pkt;
}

// TODO: Make test more clear
// CAN interface will notify us of a new packet of a selected type
void test_notification_sent_on_response_packet_receive(void)
{
    uint16_t random_test_value = 14;
    CAN_Mock::set_packet_rx(Echo_Response_Packet::serialise(random_test_value));

    setup();

    Subject<Echo_Response_Packet> *subject = interface->get_response_packet_model();

    FuncCallback<Echo_Response_Packet> cb = FuncCallback<Echo_Response_Packet>(&get_latest_response_packet);
    Observer<Echo_Response_Packet> observer(subject, &cb);

    interface->read_latest_message();
    TEST_ASSERT(response_notification_called);

    uint16_t received_value;
    latest_response_packet.deserialise(&received_value);
    TEST_ASSERT(random_test_value == received_value);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_serialise_response_to_correct_packet);
    RUN_TEST(test_deserialise_response_to_correct_packet);
    RUN_TEST(test_notification_sent_on_response_packet_receive);

    UNITY_END();
    return 0;
}