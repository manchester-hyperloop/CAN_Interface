//
//  CAN_Frame.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 14/03/2021.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef lib_CAN_Interface_CAN_Frame_hpp
#define lib_CAN_Interface_CAN_Frame_hpp

#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include <Arduino_Mock.hpp>
#endif

#define CAN_MAX_DLEN 8
typedef uint32_t canid_t;

struct CAN_Frame
{
    canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    uint8_t data[CAN_MAX_DLEN] __attribute__((aligned(8)));
};

/**
 * Copy core information from one frame to another. Useful in copying data to a 'specialised' frame.
 * @param dst - Destination frame
 * @param src - Source frame
 */
void copy_frame(CAN_Frame *dst, CAN_Frame *src);

#endif /* lib_CAN_Interface_CAN_Frame_hpp */