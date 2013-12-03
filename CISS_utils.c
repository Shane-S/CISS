#include "CISS_utils.h"

void CISS_delete_file(const char *directory, const char *filename)
{
    /* Set the directory that files will be modified in */
    char removal[NAME_BUF_SIZE];
    removal[0] = 'r';
    removal[1] = 'm';
    removal[2] = ' ';
    
    /* This section cleans out the destination directory */
    /* Create a string to concatenate the directory to clean out */
    strcat(removal, directory);
    strcat(removal, "\"");
    strcat(removal, filename);
    strcat(removal, "\"");

    /* The system code removes all files in the directory */
    system(removal);
}

void CISS_parse_filename(const char *filename, char *sensor, char *timestamp)
{
	int len = strlen(filename);
	int i;
	int j;
	int time_len;
	for(i = 0; i < len; ++i)
		if(filename[i] == '&')
			break;
	time_len = len - i;

	for(j = 0; j < i; ++j)
		sensor[j] = filename[j];
	sensor[i] = '\0';
	
	for(j = 0; j < time_len; ++j)
		timestamp[j] = filename[j + i + 1];
	timestamp[j] = '\0';
}

/**
 * Borrowed code from: http://man7.org/tlpi/code/online/dist/inotify/demo_inotify.c.html
 */

int CISS_read_filename(const char *directory, char *filename, int inotifyFd)
{
    char buf[INOT_BUF_SIZE];
    ssize_t numRead;
    struct inotify_event *event;

    inotify_add_watch(inotifyFd, directory, IN_CREATE);

	numRead = read(inotifyFd, buf, INOT_BUF_SIZE);
	if (numRead == 0 || numRead == -1)
		return -1;

	event = (struct inotify_event *) buf;
	strcpy(filename, event->name);
    return 0;
}


