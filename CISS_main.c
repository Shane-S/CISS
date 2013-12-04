#include <stdio.h>
#include "CISS_comm.h"
#include "CISS_utils.h"
#include "CISS_json_utils.h"

/* Authentication */
#define KEY 			"AC2165B6D5A198413694007924B82EB03B"
#define SECRET			"ec48b164d5ac4c6280eccfa4d61310bd"
#define CREDENTIALS		KEY ":" SECRET

/* Data endpoint (TBD) */
#define DATA_URL		

/* Sensor data directory */
#define SENSOR_DATA_DIR	"./sensor_data/"

/**
 * TODO: Revise URLs
 * TODO: Change device
 */


int main()
{
	CURL 				*handle						= 0;
	server_response		rx_buf						= {0};
	CURLcode 			result						= 0;
	struct curl_slist	*headers					= NULL;
	int 				inotifyFd 					= inotify_init();
	char 				filename[NAME_BUF_SIZE];	= {0};
	char 				sensor[NAME_BUF_SIZE];		= {0};
	char 				timestamp[NAME_BUF_SIZE];	= {0};
	int 				reading 					= 0;
	json_object 		*server_JSON				= NULL;
	
	CISS_comm_init(&handle, CREDENTIALS, &rx_buf);
	while(1)
	{
		CISS_read_file(SENSOR_DATA_DIR, filename, inotifyFd, &reading); /* Blocks until sensor proc adds to SENSOR_DATA_DIR */
		CISS_parse_filename(filename, sensor, timestamp);
		CISS_delete_file(SENSOR_DATA_DIR, filename);
		server_JSON = CISS_create_reading_JSON(sensor, timestamp, reading, "devices/ciss-I/_mac/0x298493429348329");
		CISS_send_sensor_data(handle, DATA_URL, json_object_to_json_string(server_JSON));
	}
	
	return 0;
}

