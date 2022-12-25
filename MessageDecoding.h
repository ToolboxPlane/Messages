/**
 * @file MessageDecoding.h
 * @author paul
 * @date 01.11.22
 * @brief Declaration of decoding logic for protobuf messages send via a serial interface.
 * @ingroup Messages
 */
#ifndef MESSAGES_MESSAGEDECODING_H
#define MESSAGES_MESSAGEDECODING_H

#ifndef DECODING_BUF_SIZE
    /**
     * The size of the buffer used for reception, should be at least as large as the largest possible size of the
     * message.
     */
    #define DECODING_BUF_SIZE 1024
#endif

#include <pb_decode.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Internal state of the decoder,
 */
typedef enum {
    DECODING_INITIAL,      ///< Initial state, no data received
    DECODING_END_FOUND,    ///< End byte found, waiting for start byte
    DECODING_FIRST_FOUND,  ///< Start byte received, waiting for ID
    DECODING_IN_DATA,      ///< Matching ID byte received, waiting for data or end byte
    DECODING_IN_WRONG_DATA ///< Other ID byte received, waiting for data or end byte
} message_decoding_state_t;

/**
 * All internal data of the decoder.
 */
typedef struct {
    uint8_t id;                             ///< The ID of the message to be received.
    message_decoding_state_t decodingState; ///< The state of the decoder
    uint8_t len;                            ///< The length of the received data (excluding start and ID)
    uint8_t buf[DECODING_BUF_SIZE];         ///< The buffer for the data
} message_decoding_data_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the internal state of the decoder.
 * @param decoding_data the state to initialize
 * @param message_id id of the message to be received
 */
void message_decoding_init(message_decoding_data_t *decoding_data, uint8_t message_id);

/**
 * Decode a message from a datastream.
 * @param decoding_data the internal state of the decoder
 * @param data the new byte used for decoding
 * @param fields the description of the protobuf-message
 * @param message out-parameter: set to the message if a complete message was received
 * @return true if a complete message was received, otherwise false
 * @return
 */
bool message_decoding_decode(message_decoding_data_t *decoding_data, uint8_t data, const pb_msgdesc_t *fields, void *message);

#ifdef __cplusplus
}
#endif


#endif // MESSAGES_MESSAGEDECODING_H
