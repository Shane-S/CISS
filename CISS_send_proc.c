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

/* Base API URL  */
#define BASE_URL "http://192.81.129.209"
#define API_PORT ":9090"
#define API_URL BASE_URL API_PORT

/* CISS app specifics */
#define APP_NAME "Ciss"
#define DC_NAME "Ambient.light"
#define DEV_SN "12345"
#define DEV_PROFILE "ciss1"
#define SRC_URI "devices/" DEV_PROFILE "/_sn/" DEV_SN

/* Reading endpoint */
#define READING_URL API_URL "/_apps/" APP_NAME "/_data/" DC_NAME

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
	long long int		timestamp			= 0;
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
		CISS_parse_filename(filename, sensor, &timestamp);
		CISS_delete_file(SENSOR_DATA_DIR, filename);
		server_JSON = CISS_create_reading_JSON(sensor, timestamp, reading, SRC_URI);
		/*CISS_send_data(handle, SENSOR_DATA_URL, json_object_to_json_string(server_JSON));*/
	}
	
	return 0;
}

