#ifndef CISS_FILE_UTILS_H
#define CISS_FILE_UTILS_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>

#define INOT_BUF_SIZE sizeof(struct inotify_event) * 16
#define NAME_BUF_SIZE 256

/**
 * Deletes the specified file. This is used in the main loop to delete
 * files created by the sensor reading process.
 *
 * @param directory The directory in which the file resides.
 * @param filename	The name of the file to delete.
 */
void CISS_delete_file(const char *directory, const char *filename);

/**
 * Parses a the file name of a file created by the sensor process and stores the
 * sensor name and timestamp in the corresponding variables. These will later be
 * passed CISS_create_reading_JSON.
 *
 * @param filename 	The file name to parse.
 * @param sensor	A buffer in which to store the sensor name.
 * @param timestamp Pointer to a long long int (64 bits) to store the epoch time.
 */
void CISS_parse_filename(const char *filename, char *sensor, long long int *timestamp);

/**
 * Monitors the file tree for activity and reads a file when it is closed for writing.
 * It stores the file name and reading value in the corresponding variables.
 *
 * Some code for this function was borrowed from the inotify man page,
 * http://man7.org/tlpi/code/online/dist/inotify/demo_inotify.c.html .
 *
 * @param directory The directory to monitor for changes.
 * @param filename	A buffer to hold the file name of the created file.
 * @param inotifyFd The inotify file descriptor returned by inotify_init(). 
 * @param reading	Pointer to an int which receives the sensor reading value.
 *
 * @return 0 on success, or -1 on failure. -1 will only be returned if reading the inotifyFd
 * fails.
 */
int CISS_read_file(const char *directory, char *filename, int inotifyFd, int *reading);
#endif

