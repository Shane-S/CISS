#ifndef CISS_JSON_UTILS_H
#define CISS_JSON_UTILS_H

#include <stdio.h>
#include <json/json.h>
#include "CISS_comm.h"

#define CISS_PARSE_ERROR			-1
#define CISS_STOP_IRRIGATION 		0


/**
 * Parses the command JSON received from the server and returns an int indicating
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

/**
 * Creates a JSON object containing the information from a sensor reading.
 *
 * Note that like CISS_parse_commands above, this function is for demonstration
 * only. It would need to know the destination, the tags and the location
 * to be more flexible. 
 * 
 * Also, it assumes that @params will be 1, 2 or 3 (red, blue or green). Since the
 * Python thread uses 0, 1, or 2, it subtracts 1 from this value.
 *
 * @param sensor    The sensor from which the reading came.
 * @param timestamp A timestamp indicating when the reading was taken (epoch format).
 * @param reading   The sensor reading value.
 * @param src	    URI pointing to the source of this data (i.e., from which device it came).
 *
 * @return A pointer to a json_object struct containing the sensor reading information.
 */
json_object* CISS_create_reading_JSON(const char *sensor, const long long int timestamp,
										int reading, const char *src_uri);
#endif
