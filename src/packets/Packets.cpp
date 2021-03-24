#include "Packets.hpp"

void copy_frame(can_frame *dst, can_frame *src)
{
    dst->can_dlc = src->can_dlc;
    dst->can_id = src->can_id;
    memcpy(dst->data, src->data, sizeof(uint8_t) * CAN_MAX_DLEN);
}