#ifndef CISS_COMM_H
#define CISS_COMM_H
#include <stdio.h>

/**
 * Contains the server's response.
 */
typedef struct server_response
{
	char *response;
	size_t response_size;
} server_response;

/**
 * Contains the command and parameters from the server. Currently, parameters
 * consist only of an integer for the LED colour.
 */
typedef struct CISS_command
{
	char *cmd;
	void *params;
}

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
#endif