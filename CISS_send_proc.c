#include <stdio.h>
#include <unistd.h>
#include <python2.7/Python.h>
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
 * TODO: Change devicepyinotify
 */


int main(int argc, char **argv)
{
	CURL 			*handle				= 0;
	server_response		rx_buf;
	CURLcode 		result				= 0;
	struct curl_slist	*headers			= NULL;
	int 			inotifyFd 			= inotify_init();
	char 			filename[NAME_BUF_SIZE]		= {0};
	char 			sensor[NAME_BUF_SIZE]		= {0};
	char 			timestamp[NAME_BUF_SIZE]	= {0};
	int 			reading 			= 0;
	json_object 		*server_JSON			= NULL;

	pid_t id = fork();
	if(id == 0) /* We're in the child process; run the the Python script*/
	{
		FILE *pyFile = fopen("./CISS_sensor_proc.py", "r");
		Py_SetProgramName(argv[0]);
		Py_Initialize();
		PyRun_SimpleFile(pyFile, "./CISS_sensor_proc.py");
	}
	
	/*CISS_comm_init(&handle, CREDENTIALS, &rx_buf);*/
	while(1)
	{
		CISS_read_file(SENSOR_DATA_DIR, filename, inotifyFd, &reading);
		CISS_parse_filename(filename, sensor, timestamp);
		server_JSON = CISS_create_reading_JSON(sensor, timestamp, reading, "random/src");
	}
	
	return 0;
}

