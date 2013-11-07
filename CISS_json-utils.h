#ifndef CISS_JSON-UTILS_H
#define CISS_JSON-UTILS_H

#include <stdio.h>
#include <json/json.h>
#include "CISS_comm.h"

/**
 * Parses the command and parameters held in a JSON object and stores them in a
 * CISS_command structure (from which it will be easier to write to a command
 * file).
 *
 * @param jobj Pointer to the JSON object to be parsed.
 * @param cmds Pointer to the CISS_command structure to hold command/params.
 */
void CISS_parse_commands(json_object *jobj, CISS_command *cmd);

#endif