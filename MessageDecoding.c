/**
 * @file MessageDecoding.c
 * @author paul
 * @date 01.11.22
 * Description here TODO
 */
#include "MessageDecoding.h"

#include "MessageDefs.hpp"

bool decode_message(decoding_data_t *decoding_data, uint8_t data, pb_istream_t *istream) {
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

                    *istream = pb_istream_from_buffer(decoding_data->buf, decoding_data->len);

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
