/**
 * @file MessageDecoding.c
 * @author paul
 * @date 01.11.22
 * @brief Implementation of decoding logic for protobuf messages send via a serial interface.
 * @ingroup Messages
 */
#include "MessageDecoding.h"

#include "MessageDefs.h"

void message_decoding_init(message_decoding_data_t *decoding_data, uint8_t message_id, const pb_msgdesc_t *fields) {
    decoding_data->_decodingState = DECODING_INITIAL;
    decoding_data->_len = 0;
    decoding_data->_id = message_id;
    decoding_data->_fields = fields;
}

bool message_decoding_decode(message_decoding_data_t *decoding_data, uint8_t data, void *message) {
    switch (decoding_data->_decodingState) {
        case DECODING_INITIAL:
            if (data == END_BYTE) {
                decoding_data->_decodingState = DECODING_INITIAL_END_FOUND;
            }
            break;
        case DECODING_INITIAL_END_FOUND:
            if (data == START_BYTE) {
                decoding_data->_decodingState = DECODING_START_FOUND;
            } else {
                decoding_data->_decodingState = DECODING_INITIAL;
            }
            break;
        case DECODING_START_FOUND:
            if (data == decoding_data->_id) {
                decoding_data->_decodingState = DECODING_IN_DATA;
                decoding_data->_len = 0;
            } else {
                decoding_data->_decodingState = DECODING_IN_WRONG_DATA;
            }
            break;
        case DECODING_IN_DATA:
            if (data == END_BYTE) {
                decoding_data->_decodingState = DECODING_IN_DATA_END_FOUND;
            }
            decoding_data->_buf[decoding_data->_len] = data;
            decoding_data->_len += 1;
            break;
        case DECODING_IN_DATA_END_FOUND:
            if (data == START_BYTE) {
                decoding_data->_decodingState = DECODING_START_FOUND;
                pb_istream_t istream = pb_istream_from_buffer(decoding_data->_buf, decoding_data->_len - 1);
                pb_decode(&istream, decoding_data->_fields, message);
                return true;
            } else {
                decoding_data->_decodingState = DECODING_IN_DATA;
            }
            break;
        case DECODING_IN_WRONG_DATA:
            if (data == END_BYTE) {
                decoding_data->_decodingState = DECODING_IN_WRONG_DATA_END_FOUND;
            }
            break;
        case DECODING_IN_WRONG_DATA_END_FOUND:
            if (data == START_BYTE) {
                decoding_data->_decodingState = DECODING_START_FOUND;
            } else {
                decoding_data->_decodingState = DECODING_IN_WRONG_DATA;
            }
            break;
    }
    return false;
}
