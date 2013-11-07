#include <stdio.h>
#include <string.h>
#include <json/json.h>

/**
 * TODO: Add JSON object creation code (packages sensor data into JSON 
 *		 objects).
 * TODO: Parse agreed-upon commands from the server (implement
 * 		 CISS_parse_commands).
 * TODO: Remove extraneous test code (enum CISS_response_type, for example).
 */

enum CISS_response_type
{
	CISS_response_command,
	CISS_response_info
};

int main(void)
{
	size_t 					i 			= 0;
	const char				*data_store	= "{ \"type\" : \"command\", \"destination\" : \"sensor1\"}";
	json_object 			*jobj		= json_tokener_parse(data_store);
	enum json_type 			type;
	enum CISS_response_type response;
	int	 					destination;
	
	json_object_object_foreach(jobj, key, val)
	{
		type = json_object_get_type(val);
		if(type == json_type_string)
		{
			const char *value = json_object_get_string(val);
			if(strcmp(key, "type") == 0)
			{
				if(strcmp(value, "command") == 0)
				{
					response = CISS_response_command;
				}
				else if(strcmp(value, "info") == 0)
				{
					response = CISS_response_info;
				}
				else
				{
					printf("Error: invalid response type (must be command or info).\n");
				}
			}
			else if(strcmp(key, "destination") == 0)
			{
				if(strcmp(value, "sensor1") == 0)
				{
					destination = 1;
				}
				/* and so on */
				else
				{
					printf("Error: invalid destination.\n");
				}
			}
		}
	}

	printf("The type is %s.\n", (response == CISS_response_command) ? "command" : "info");
	printf("The destination is sensor %d.\n", destination);
	return 0;
}
