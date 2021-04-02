#ifndef lib_CAN_Interface_CAN_Interface_hpp
#define lib_CAN_Interface_CAN_Interface_hpp

#include <Notifications.hpp>
#include <Log.hpp>

#include "Packets.hpp"

#ifndef UNIT_TEST
#include <mcp2515.h>
#else
#include <MCP2515_Mock.hpp>
#endif

class CAN_Interface
{
#ifndef UNIT_TEST
	MCP2515 CAN;
#else
	// Mock
	MCP2515 CAN;
#endif

	/// echo request frame model to be subscribed to
	Subject<Echo_Request_Packet> latest_echo_request_frame;
	/// echo response frame model to be subscribed to
	Subject<Echo_Response_Packet> latest_echo_response_frame;

public:
	/**
     * Constructor. Assigns the CS pin for the CAN module
     * @param CS_pin pin number of the chip select pin used
     */
	CAN_Interface(uint8_t CS_pin = 10);

	/**
     * Initialise the connected CAN module
     * @return true on success, false otherwise
     */
	bool init(CAN_SPEED bit_rate = CAN_500KBPS, CAN_CLOCK clock_speed = MCP_16MHZ);

	/**
     * Send a frame across the CAN bus
     * @param frame - Frame to send 
     * @return true on success, false otherwise
     */
	bool send(can_frame *frame);

	/**
     * Read the latest message from the CAN bus. This should be called regularly
     */
	void read_latest_message();

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
     * @param frame A pointer to the frame to parse
     * @return true if packet parsed successfully, false otherwise
     */
	bool parse_and_update(can_frame *frame);
};

#endif /* lib_CAN_Interface_CAN_Interface_hpp */