/**
 * @file MessageDecoding.c
 * @author paul
 * @date 01.11.22
 * @brief Implementation of decoding logic for protobuf messages send via a serial interface.
 * @ingroup Messages
 */
#include "MessageDecoding.h"

#include "MessageDefs.h"

void message_decoding_init(message_decoding_data_t *decoding_data, uint8_t message_id) {
    decoding_data->decodingState = DECODING_INITIAL;
    decoding_data->len = 0;
    decoding_data->id = message_id;
}

bool message_decoding_decode(message_decoding_data_t *decoding_data, uint8_t data, const pb_msgdesc_t *fields,
                             void *message) {
    switch (decoding_data->decodingState) {
        case DECODING_INITIAL:
            if (data == END_BYTE) {
                decoding_data->decodingState = DECODING_END_FOUND;
            }
            break;
        case DECODING_END_FOUND:
            if (data == START_BYTE) {
                decoding_data->decodingState = DECODING_FIRST_FOUND;
                if (decoding_data->len > 0) {
                    decoding_data->len -= 1;

                    pb_istream_t istream = pb_istream_from_buffer(decoding_data->buf, decoding_data->len);
                    pb_decode(&istream, fields, message);

                    decoding_data->len = 0;
                    return true;
                }
            } else {
                if (decoding_data->len == 0) {
                    decoding_data->decodingState = DECODING_INITIAL;
                } else {
                    decoding_data->decodingState = DECODING_IN_DATA;
                    decoding_data->buf[decoding_data->len] = data;
                    decoding_data->len += 1;
                }
            }
            break;
        case DECODING_FIRST_FOUND:
            if (data == decoding_data->id) {
                decoding_data->decodingState = DECODING_IN_DATA;
            } else {
                decoding_data->decodingState = DECODING_IN_WRONG_DATA;
            }
            break;
        case DECODING_IN_DATA:
            if (data == END_BYTE) {
                decoding_data->decodingState = DECODING_END_FOUND;
            }
            decoding_data->buf[decoding_data->len] = data;
            decoding_data->len += 1;
            break;
        case DECODING_IN_WRONG_DATA:
            if (data == END_BYTE) {
                decoding_data->decodingState = DECODING_END_FOUND;
            }
            break;
    }
    return false;
}
