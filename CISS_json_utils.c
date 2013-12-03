#include <stdio.h>
#include <string.h>
#include "CISS_json_utils.h"

int CISS_parse_commands(const char *command_string)
{
	json_object 	*server_cmd	= json_tokener_parse(command_string);
	json_object		*cmd_obj;
	json_object		*params_obj;
	const char		*cmd;
	int 			command 	= CISS_PARSE_ERROR;
	
	cmd_obj = json_object_object_get(server_cmd, "@command");
	cmd = json_object_get_string(cmd_obj);
	if(strcmp(cmd, "stop-irrigation") == 0)
		return CISS_STOP_IRRIGATION;
	
	params_obj = json_object_object_get(server_cmd, "@params");
	command = json_object_get_int(params_obj) - 1;

	/* Free the objects */
	json_object_put(cmd_obj);
	json_object_put(params_obj);

	return command;
}

json_object* CISS_create_reading_JSON(const char *sensor, const char *timestamp,
										int reading, const char *src)
{
	/* For our program, these won't change between readings */
	json_object *tags			= json_object_new_array();
	json_object *tag1			= json_object_new_string("sensor");
	json_object *tag2			= json_object_new_string("demo");
	json_object *loc			= json_object_new_object();
	json_object *name			= json_object_new_string("home");
	
	json_object *sensor_JSON 	= json_object_new_object();
	json_object *points			= json_object_new_array();
	json_object *datapoint		= json_object_new_object();
	json_object *src_uri		= json_object_new_string(src);
	json_object *time			= json_object_new_string(timestamp);
	json_object *value			= json_object_new_int(reading);
	json_object *dst			= json_object_new_object();
	json_object *channel		= json_object_new_string(sensor);
	
	/* Construct tags array and loc object */
	json_object_array_add(tags, tag1);
	json_object_array_add(tags, tag2);
	json_object_object_add(loc, "name", name);

	/* Construct the datapoint */
	json_object_object_add(dst, "channel", channel);
	json_object_object_add(datapoint, "dst", dst);
	json_object_object_add(datapoint, "time", time);
	json_object_object_add(datapoint, "value", value);
	
	/* Add it to the array of datapoints */
	json_object_array_add(points, datapoint);

	/* Add all objects to the returned object */
	json_object_object_add(sensor_JSON, "tags", tags);
	json_object_object_add(sensor_JSON, "loc", loc);
	json_object_object_add(sensor_JSON, "src_uri", src_uri);
	json_object_object_add(sensor_JSON, "datapoints", points);

	return sensor_JSON;
}
