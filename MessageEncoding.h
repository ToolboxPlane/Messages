/**
 * @file MessageEncoding.h
 * @author paul
 * @date 23.10.22
 * @brief Declaration of encoding logic for protobuf messages send via a serial interface.
 * @ingroup Messages
 */
#ifndef MESSAGES_MESSAGEENCODING_H
#define MESSAGES_MESSAGEENCODING_H

#include <pb_encode.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Encode a message
 * @param buf the buffer to write to needs to be at least the size of the message + 3
 * @param size the size of the buffer
 * @param fields the protobuf field description
 * @param message a pointer to the message to encode
 * @param id the message if of the message
 * @return the size of the encoded message
 */
uint16_t message_encode(uint8_t *buf, uint16_t size, const pb_msgdesc_t *fields, const void *message, uint8_t id);

#ifdef __cplusplus
}
#endif

#endif // MESSAGES_MESSAGEENCODING_H
