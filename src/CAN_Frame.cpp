#include "CAN_Frame.hpp"

void specialise_abstract_frame(CAN_Frame *dst, CAN_Frame *src)
{
    dst->can_dlc = src->can_dlc;
    dst->can_id = src->can_id;
    memcpy(dst->data, src->data, sizeof(uint8_t) * CAN_MAX_DLEN);
}
