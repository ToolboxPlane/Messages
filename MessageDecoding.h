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
    DECODING_INITIAL,           ///< Initial state, no data received
    DECODING_END_FOUND,         ///< End found, not in package
    DECODING_START_FOUND,       ///< Start byte received, waiting for ID
    DECODING_IN_DATA,           ///< Matching ID byte received, waiting for data or end byte
    DECODING_IN_DATA_END_FOUND, ///< End byte found, currently in correct package
} message_decoding_state_t;

/**
 * All internal data of the decoder.
 */
typedef struct {
    uint8_t _id;                             ///< The ID of the message to be received.
    const pb_msgdesc_t *_fields;             ///< Protobuf message description
    message_decoding_state_t _decodingState; ///< The state of the decoder
    uint8_t _len;                            ///< The length of the received data (excluding start and ID)
    uint8_t _buf[DECODING_BUF_SIZE];         ///< The buffer for the data
} message_decoding_data_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the internal state of the decoder.
 *
 * This function performs the following tasks:
 *  * Set the internal variable "ID" to the argument message_id
 *  * Set the internal variable "fields" to the argument "fields"
 *  * Initialize decoding data such that the internal state machine is in the init state
 *
 * @param decoding_data the state to initialize
 * @param message_id id of the message to be received
 * @param fields the description of the protobuf-message
 */
void message_decoding_init(message_decoding_data_t *decoding_data, uint8_t message_id, const pb_msgdesc_t *fields);

/**
 * @brief Decode a message from a datastream.
 *
 * The function performs the following tasks:
 *  * Transition the internal state machine with the input "data" in accordance to the following state machine:
 * \dot
 *  digraph {
 *      rankdir = "LR";
 *      INITIAL -> END_FOUND [
 *          label = "data=0xF0";
 *      ]
 *
 *      INITIAL -> INITIAL [
 *          label = "otherwise";
 *      ]
 *
 *      END_FOUND -> INITIAL [
 *          label = "otherwise";
 *      ]
 *
 *      END_FOUND -> START_FOUND [
 *          label = "data=0x0F";
 *      ]
 *
 *      IN_DATA_END_FOUND -> IN_DATA [
 *          label = "otherwise";
 *      ]
 *
 *      IN_DATA_END_FOUND -> START_FOUND [
 *          label = "data=0x0F/\nPublish data";
 *      ]
 *
 *      START_FOUND -> IN_DATA [
 *          label = "data=ID/\nInit buffer";
 *      ]
 *
 *      IN_DATA -> IN_DATA [
 *          label = "otherwise/\nFill buffer";
 *      ]
 *
 *      IN_DATA -> IN_DATA_END_FOUND [
 *          label = "data=0xF0/\nFill buffer";
 *      ]
 *
 *      START_FOUND -> INITIAL [
 *          label = "otherwise";
 *      ]
 *  }
 * \enddot
 *  * with the following actions:
 *      * **Init buffer**: Clear the internal buffer to contain no items
 *      * **Fill buffer**: Append "data" to the internal buffer
 *      * **Publish data**: Performs the following operations:
 *          * Remove the last (latest) element (which is the end byte) from the buffer
 *          * Prepare the buffer for protobuf (::pb_istream_from_buffer)
 *          * Set "message" to the decoded message (::pb_decode)
 *          * Return true
 *  * if the **Publish data** was not taken, return false
 *
 * @param decoding_data the internal state of the decoder
 * @param data the new byte used for decoding
 * @param message out-parameter: set to the message if a complete message was received
 * @return true if a complete message was received, otherwise false
 * @return
 */
bool message_decoding_decode(message_decoding_data_t *decoding_data, uint8_t data, void *message);

#ifdef __cplusplus
}
#endif


#endif // MESSAGES_MESSAGEDECODING_H
