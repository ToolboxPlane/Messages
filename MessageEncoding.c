/**
 * @file MessageEncoding.c
 * @author paul
 * @date 23.10.22
 * Description here TODO
 */
#include "MessageEncoding.h"

#include "MessageDefs.hpp"

uint16_t message_encode(uint8_t *buf, uint16_t size, const pb_msgdesc_t *fields, const void *message, uint8_t id) {
    pb_ostream_t ostream = pb_ostream_from_buffer(buf + 2, size - 3);
    pb_encode(&ostream, fields, message);
    buf[0] = START_BYTE;
    buf[1] = id;
    buf[ostream.bytes_written + 2] = END_BYTE;
    return ostream.bytes_written + 3;
}
