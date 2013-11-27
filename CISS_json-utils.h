#ifndef CISS_JSON_UTILS_H
#define CISS_JSON_UTILS_H

#include <stdio.h>
#include <json-c/json.h>
#include "CISS_comm.h"

#define CISS_PARSE_ERROR			-1
#define CISS_STOP_IRRIGATION 		0
#define CISS_START_IRRIGAION_RED	1
#define CISS_START_IRRIGATION_BLUE	2
#define CISS_START_IRRIGATION_GREEN 3


/**
 * Parses the commands received from the server and returns an int indicating
 * the command.
 * 
 * This function is currently for demonstration purposes only; it assumes that
 * any keys other than "@command" and "@params" are invalid, and that the only
 * valid type for the value of "@params" is an int. It will print an error
 * message to stderr and return CISS_PARSE_ERROR if any other cases are
 * encountered.
 *
 * @param command_string The command string retrieved from the server.
 * @return Integer indicating the server's command or -1 on error.
 */
int CISS_parse_commands(const char *command_string);

#endif