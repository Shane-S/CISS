#include <stdio.h>
#include "CISS_comm.h"
#include "CISS_utils.h"
#include "CISS_json_utils.h"

#define KEY 	"AC2165B6D5A198413694007924B82EB03B"
#define SECRET	"ec48b164d5ac4c6280eccfa4d61310bd"

/**
 * TODO: Perform error checking.
 * TODO: Monitor sensor_data directory and read data to send.
 * TODO: Split into functions (reading data from files, posting data to server,
		 polling for response (separate thread)).
 */


int main()
{
	#if 0
	CURL 		*handle					= 0;
	const char 	*credentials 			= KEY ":" SECRET;
	const char	*channel_URL			= "http://birol.dlinkddns.com:19090/v1/apps/ciss/stores/sensor-data/channels";
	const char	*data_URL				= "http://birol.dlinkddns.com:19090/v1/apps/ciss/data/sensor-data";
	server_response		rx_buf			= {0};
	CURLcode 			result			= 0;
	struct curl_slist	*headers		= NULL;
	#endif
	int inotifyFd = inotify_init();
	char filename[NAME_BUF_SIZE];
	char sensor[NAME_BUF_SIZE];
	char timestamp[NAME_BUF_SIZE];
	int reading = 0;
	json_object *server_JSON;
	
	while(1)
	{
		CISS_read_file("./testdir", filename, inotifyFd, &reading);
		CISS_parse_filename(filename, sensor, timestamp);
		CISS_delete_file("testdir/", filename);
		server_JSON = CISS_create_reading_JSON(sensor, timestamp, reading, "devices/ciss-I/_mac/0x298493429348329");
		printf("The JSON:\n\n %s\n", json_object_to_json_string(server_JSON));
	}
	
	#if 0
	curl_slist_free_all(headers);
	curl_easy_cleanup(handle);
	#endif

	return 0;
}

