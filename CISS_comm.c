#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "curltest.h"
#include <json/json.h>

#define KEY 	"AK7F3095A614484A5EBC911649BD320F72"
#define SECRET 	"9b003d4267da4e7490d4db8b552a8465"

/**
 * TODO: Write JSON strings using json-c library.
 * TODO: Perform error checking.
 * TODO: Monitor sensor_data directory and read data to send.
 * TODO: Split into functions (reading data from files, posting data to server,
		 polling for response (separate thread)).
 */

int main()
{
	CURL 		*handle					= 0;
	const char 	*credentials 			= KEY ":" SECRET;
	const char	*channel_URL			= "http://birol.dlinkddns.com:19090/v1/apps/ciss/stores/sensor-data/channels";
	const char	*data_URL				= "http://birol.dlinkddns.com:19090/v1/apps/ciss/data/sensor-data";
	server_response		rx_buf			= {0};
	CURLcode 			result			= 0;
	struct curl_slist	*headers		= NULL;
	
	curl_global_init(CURL_GLOBAL_ALL);
	
	/* Set headers to send along with each request. */
	headers = curl_slist_append(headers, "Content-type: application/json");
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0");
	
	handle 	= curl_easy_init();
	
	curl_easy_setopt(handle, CURLOPT_USERPWD, credentials);	/* Set basic authentication header */
	curl_easy_setopt(handle, CURLOPT_AUTOREFERER, 1);		/* libcURL will set the Referer header when redirected */
	curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);	/* libcURL will follow redirects */
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);	/* Headers to send with the request */
	curl_easy_setopt(handle, CURLOPT_POST, 1);				/* libcURL will POST data until set otherwise */
	
	/* Sends the data to the server; move this into a function. */
	#if 0
	curl_easy_setopt(handle, CURLOPT_URL, data_URL);
	curl_easy_setopt(handle, CURLOPT_POSTFIELDS, test_data);
	result = curl_easy_perform(handle);
	#endif

	curl_slist_free_all(headers);
	curl_easy_cleanup(handle);

	return 0;
}

size_t WriteResponseCallback(char *rx_data, size_t rx_data_size,
							size_t rx_data_nmemb, void *rx_buf)
{
	size_t actual_size 	= rx_data_size * rx_data_nmemb;
	CISS_Response *buf 	= (server_response *)rx_buf;
	buf->response 		= (char *)malloc(actual_size + 1); /* Add 1 in case not null terminated */
	
	if(buf->response)
	{
		memcpy(buf->response, rx_data, actual_size);	/* Copy response to buffer */
		buf->response[actual_size] = '\0'; 				/* Zero the last byte (null terminate response) */
		buf->response_size = actual_size;				/* Set the actual size of the response */
	}
	
	return actual_size;
}

