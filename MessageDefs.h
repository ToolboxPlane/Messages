/**
 * @file MessageDefs.h
 * @author paul
 * @date 01.11.22
 * @brief Declaration of constants for message decoding and encoding
 * @ingroup Messages
 */
#ifndef MESSAGES_MESSAGEDEFS_H
#define MESSAGES_MESSAGEDEFS_H

/**
 * @defgroup Messages Toolbox-Plane Messages Library
 * @brief Library for the declaration of all messages and helper functions for coding and decoding.
 */

/**
 * Start byte for encoding
 */
enum { START_BYTE = 0x0F };

/**
 * End byte for encoding
 */
enum { END_BYTE = 0xF0 };

#endif // MESSAGES_MESSAGEDEFS_H
