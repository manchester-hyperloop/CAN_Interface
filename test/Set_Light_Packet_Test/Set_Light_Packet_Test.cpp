#include <cstddef>
#include <unity.h>
#include <Instance.hpp>
#include <Notifications.hpp>
#include <CAN_Mock.hpp>

#define CAN_PACKET_SET_LIGHT
#include <CAN_Interface.hpp>

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
void test_serialise_request_to_correct_packet(void)
{
    uint16_t random_test_value = 13;
    can_frame test_frame = Set_Light_Packet::serialise(random_test_value);

    // Check that the id is set correctly
    TEST_ASSERT_EQUAL(test_frame.can_id, Packet_Priority::CAN_PRIORITY_SET_LIGHT);

    // Check that the data and length of data has been set correctly
    uint16_t compiled_value = 0;
    memcpy(&compiled_value, &test_frame.data, sizeof(compiled_value));
    TEST_ASSERT_EQUAL(compiled_value, random_test_value);
    TEST_ASSERT_EQUAL(test_frame.can_dlc, sizeof(random_test_value));
}

// Parser will parse into correct message type
void test_deserialise_request_to_correct_packet(void)
{
    uint16_t random_test_value = 14;
    Set_Light_Packet packet = Set_Light_Packet::serialise(random_test_value);

    uint16_t parsed_value;
    packet.deserialise(&parsed_value);
    TEST_ASSERT_EQUAL(random_test_value, parsed_value);
}

bool request_notification_called = false;
Set_Light_Packet latest_request_packet;
void get_latest_request_packet(Set_Light_Packet pkt)
{
    request_notification_called = true;
    latest_request_packet = pkt;
}

// TODO: Make test more clear
// CAN interface will notify us of a new packet of a selected type
void test_notification_sent_on_request_packet_receive(void)
{
    uint16_t random_test_value = 14;
    CAN_Mock::set_packet_rx(Set_Light_Packet::serialise(random_test_value));

    setup();

    Subject<Set_Light_Packet> *subject = interface->get_set_light_subject();

    FuncCallback<Set_Light_Packet> cb = FuncCallback<Set_Light_Packet>(&get_latest_request_packet);
    Observer<Set_Light_Packet> observer(subject, &cb);

    interface->read_latest_message();
    TEST_ASSERT(request_notification_called);

    uint16_t received_value;
    latest_request_packet.deserialise(&received_value);
    TEST_ASSERT(random_test_value == received_value);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_serialise_request_to_correct_packet);
    RUN_TEST(test_deserialise_request_to_correct_packet);
    RUN_TEST(test_notification_sent_on_request_packet_receive);

    UNITY_END();
    return 0;
}