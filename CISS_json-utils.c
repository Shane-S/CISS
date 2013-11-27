#include <stdio.h>
#include <string.h>
#include "CISS_json-utils.h"

/**
 * TODO: Add JSON object creation code (packages sensor data into JSON 
 *		 objects).
 */

int CISS_parse_commands(const char *command_string)
{
	json_object 	*jobj = json_tokener_parse(command_string);
	enum json_type 	type;
	int 			command = CISS_PARSE_ERROR;
	
	json_object_object_foreach(jobj, key, val)
	{
		type = json_object_get_type(val);
		switch(type)
		{
			case json_type_string:
			{
				const char *value = json_object_get_string(val);
				if(strcmp(key, "@command") != 0)
				{
					fprintf(stderr, "Invalid value \"%s\" encountered for key \"%s\".\n", value, key);
					return CISS_PARSE_ERROR;
				}
				
				if(strcmp(value, "stop-irrigation") == 0)
				{
					command = CISS_STOP_IRRIGATION;
				}
				else if(strcmp(value, "start-irrigation") != 0) /* I.e., this is neither "stop-irrigation" nor "start-irrigation" */
				{
					fprintf(stderr, "Error: invalid command (expected \"start-irrigation\" or \"stop-irrigation\").\n");
					return CISS_PARSE_ERROR;
				}
			}
			break;
			
			case json_type_int:
			{
				const int colour = json_object_get_int(val);
				if(strcmp(key, "@params") != 0 || 
				   !(colour >= 0 && colour <=2))
				{
					fprintf(stderr, "Invalid value \"%d\" encountered for key \"%s\".\n", colour, key);
					return CISS_PARSE_ERROR;
				}
				
				command = colour + 1;
			}
			break;
			
			default:
				return CISS_PARSE_ERROR;
		}	
	}
	
	return command;
}