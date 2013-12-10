#ifndef CISS_COMM_H
#define CISS_COMM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json/json.h>

/**
 * Contains the server's response.
 *
 * Note: make sure to free() response after use, because the WriteResponseCallback
 * function will malloc it every time.
 */
typedef struct server_response
{
	char *response;
	size_t response_size;
} server_response;

/**
 * Writes the server's response to a buffer.
 *
 * @param rx_data 		A pointer to data received from the server.
 * @param rx_data_size	Size of each member in the response.
 * @param rx_data_nmemb	The number of members in the response.
 * @param buffer		The buffer to contain the response for future use.
 *
 * @return				The number of bytes handled by the function. If this
 *						differs from the number passed in, libcurl will abort
 *						the operation.
 */
size_t WriteResponseCallback(char *rx_data, size_t rx_data_size, 
							size_t rx_data_nmemb, void *rx_buf);

/**
 * Initialises communications parameters: sets the headers (content type, user agent and basic authentication),
 * tells libcURL to follow redirects, and sets the user agent.
 *
 * @param handle:		A handle to be passed in to other libcURL functions. It's initialised to the value returned
 *						by curl_easy_init().
 * @param credentials: 	The username and password (or key and secret, in this case) separated by ":".
 * @param buf:			Pointer to a buffer structure to hold the server's response to GET requests.
 * @param headers:		A singly-linked list of headers to include with each request.
 */
void CISS_comm_init(CURL **handle, const char *credentials, server_response *buf, struct curl_slist *headers);

/**
 * Sends a JSON object containing the sensor reading and other necessary information to the endpoint
 * specified by data_URL.
 *
 * @param handle: 	The libcURL handle to pass to curl_easy_perform().
 * @param data_URL:	The destination URL for the data in the form API_URL + '/_apps/' + app_name + '/_data/' + dc_name.
 * @param data:		The JSON string to send.
 */
void CISS_send_sensor_data(CURL *handle, const char *data_URL, const char *data);

/**
 * Gets a command from the server.
 *
 * @param handle: 	The handle to pass to curl_easy_perform.
 * @param cmd_URL:	The URL from which to GET commands.
 */
void CISS_get_commands(CURL *handle, const char *cmd_URL);
#endif
