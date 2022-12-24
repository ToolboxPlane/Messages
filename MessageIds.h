/**
 * @file MessageIds.h
 * @author paul
 * @date 23.10.22
 * @brief Declaration of the IDs of the used messages
 * @ingroup Messages
 */
#ifndef MESSAGES_MESSAGEIDS_H
#define MESSAGES_MESSAGEIDS_H

/**
 * Id of the message send from the flightcontroller to the flightcomputer.
 */
enum { FC_ID = 0x10 };

/**
 * Id of the message send from the PDB to the flightcomputer.
 */
enum { PDB_ID = 0x30 };

/**
 * Id of the message send from the flightcomputer to the flightcontroller (i.e. the setpoint).
 */
enum { FC_SP_ID = 0x40 };

#endif // MESSAGES_MESSAGEIDS_H
