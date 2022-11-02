/**
 * @file MessageEncoding.h
 * @author paul
 * @date 23.10.22
 * Description here TODO
 */
#ifndef FLIGHTCOMPUTER_MESSAGEENCODING_H
#define FLIGHTCOMPUTER_MESSAGEENCODING_H

#include <pb_encode.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint16_t encode_message(uint8_t *buf, uint16_t size, const pb_msgdesc_t *fields, const void *message, uint8_t id);

#ifdef __cplusplus
}
#endif

#endif // FLIGHTCOMPUTER_MESSAGEENCODING_H
