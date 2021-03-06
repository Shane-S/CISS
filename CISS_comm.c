#include "CISS_comm.h"

size_t WriteResponseCallback(char *rx_data, size_t rx_data_size,
							size_t rx_data_nmemb, void *rx_buf)
{
	size_t 			actual_size = rx_data_size * rx_data_nmemb;
	server_response *buf		= (server_response *)rx_buf;
	
	buf->response = (char *)malloc(actual_size + 1); 	/* Add 1 in case not null terminated */
	if(buf->response)
	{
		memcpy(buf->response, rx_data, actual_size);	/* Copy response to buffer */
		buf->response[actual_size] = '\0'; 				/* Zero the last byte (null terminate response) */
		buf->response_size = actual_size;				/* Set the actual size of the response */
	}
	
	return actual_size;
}

void CISS_comm_init(CURL **handle, const char *credentials, server_response *buf, struct curl_slist *headers)
{
	curl_global_init(CURL_GLOBAL_ALL);
	
	/* Set headers to send along with each request. */
	headers = curl_slist_append(headers, "Content-type: application/json");
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0");
	
	*handle 	= curl_easy_init();
	
	curl_easy_setopt(handle, CURLOPT_USERPWD, credentials);					/* Set basic authentication header */
	curl_easy_setopt(handle, CURLOPT_AUTOREFERER, 1);						/* libcURL will set the Referer header when redirected */
	curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);					/* libcURL will follow redirects */
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);					/* Tell libcURL to include headers in list defined above */
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteResponseCallback);	/* Function called to write response of a GET to buffer */
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, buf);						/* GET responses will be written to buf */
}

void CISS_send_sensor_data(CURL *handle, const char *data_URL, const char *data)
{
	curl_easy_setopt(handle, CURLOPT_POST, 1);				/* libcURL will POST data until set otherwise */
	curl_easy_setopt(handle, CURLOPT_URL, data_URL);
	curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data);
	curl_easy_perform(handle);
}

void CISS_get_commands(CURL *handle, const char *cmd_URL)
{
	curl_easy_setopt(handle, CURLOPT_HTTPGET, 1);	/* Must explicitly tell libcURL to use GET */
	curl_easy_setopt(handle, CURLOPT_URL, cmd_URL);
	curl_easy_perform(handle);
}

