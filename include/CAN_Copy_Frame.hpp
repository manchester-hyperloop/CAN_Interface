//
//  CAN_Copy_Frame.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 14/03/2021.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef lib_CAN_Interface_CAN_Copy_Frame_hpp
#define lib_CAN_Interface_CAN_Copy_Frame_hpp

#ifndef UNIT_TEST
#include <Arduino.h>
#include <mcp2515.h>
#else
#include <Arduino_Mock.hpp>
#include <MCP2515_Mock.hpp>
#endif

/**
 * Copy core information from one frame to another. Useful in copying data to a 'specialised' frame.
 * @param dst - Destination frame
 * @param src - Source frame
 */
void copy_frame(can_frame *dst, can_frame *src);

#endif /* lib_CAN_Interface_CAN_Copy_Frame_hpp */