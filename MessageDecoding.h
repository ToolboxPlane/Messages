/**
 * @file MessageDecoding.h
 * @author paul
 * @date 01.11.22
 * Description here TODO
 */
#ifndef FLIGHTCOMPUTER_MESSAGEDECODING_H
#define FLIGHTCOMPUTER_MESSAGEDECODING_H

#ifndef DECODING_BUF_SIZE
    #define DECODING_BUF_SIZE 128
#endif

#include <pb_decode.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    DECODING_INITIAL,
    DECODING_END_FOUND,
    DECODING_FIRST_FOUND,
    DECODING_IN_DATA,
    DECODING_IN_WRONG_DATA
} message_decoding_state_t;

typedef struct DecodingData {
    uint8_t id;
    message_decoding_state_t decodingState;
    uint8_t len;
    uint8_t buf[DECODING_BUF_SIZE];
} message_decoding_data_t;

#ifdef __cplusplus
extern "C" {
#endif

bool message_decode(message_decoding_data_t *decoding_data, uint8_t data, pb_istream_t *istream);

#ifdef __cplusplus
}
#endif


#endif // FLIGHTCOMPUTER_MESSAGEDECODING_H
