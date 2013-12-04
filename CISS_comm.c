#include "CISS_comm.h"

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

void CISS_comm_init(CURL **handle, 	struct curl_slist *headers, const char *credentials)
{
	curl_global_init(CURL_GLOBAL_ALL);
	
	/* Set headers to send along with each request. */
	headers = curl_slist_append(headers, "Content-type: application/json");
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0");
	
	*handle 	= curl_easy_init();
	
	curl_easy_setopt(handle, CURLOPT_USERPWD, credentials);	/* Set basic authentication header */
	curl_easy_setopt(handle, CURLOPT_AUTOREFERER, 1);		/* libcURL will set the Referer header when redirected */
	curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);	/* libcURL will follow redirects */
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);	/* Headers to send with the request */
}

void CISS_send_sensor_data(CURL *handle, const char *data_URL, const char *data)
{
	curl_easy_setopt(handle, CURLOPT_POST, 1);				/* libcURL will POST data until set otherwise */
	
	/* Sends the data to the server; move this into a function. */
	curl_easy_setopt(handle, CURLOPT_URL, data_URL);
	curl_easy_setopt(handle, CURLOPT_POSTFIELDS, test_data);

	curl_easy_perform(handle);
}

void CISS
