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
    sprintf(removal + 3, "\"%s%s\"", directory, filename);

    /* The system code removes all files in the directory */
    system(removal);
}

void CISS_parse_filename(const char *filename, char *sensor, long long int *timestamp)
{
	int len = strlen(filename);
	int i;
	int j;
	int time_len;
	char temp_time[256] = {0};
	for(i = 0; i < len; ++i)
		if(filename[i] == '&')
			break;
	time_len = len - i;

	for(j = 0; j < i; ++j)
		sensor[j] = filename[j];
	sensor[i] = '\0';
	
	for(j = 0; j < time_len; ++j)
		temp_time[j] = filename[j + i + 1];
	temp_time[j] = '\0';
	sscanf(temp_time, "%lld", timestamp);
}

/**
 * Borrowed code from: http://man7.org/tlpi/code/online/dist/inotify/demo_inotify.c.html
 */

int CISS_read_file(const char *directory, char *filename, int inotifyFd, int *reading)
{
    char buf[INOT_BUF_SIZE];
    char file_contents[64] = {0};
    char path[NAME_BUF_SIZE] = {0};
    FILE *written;
    ssize_t numRead;
    struct inotify_event *event;

    inotify_add_watch(inotifyFd, directory, IN_CLOSE_WRITE);

	numRead = read(inotifyFd, buf, INOT_BUF_SIZE);
	if (numRead == 0 || numRead == -1)
		return -1;

	event = (struct inotify_event *) buf;
	strcpy(filename, event->name);
	sprintf(path, "%s", directory);
	sprintf(path + strlen(directory), "%c", '/');
	sprintf(path + strlen(directory) + 1, "%s", filename);
	
	written = fopen(path, "r");
	fgets(file_contents, 64, written);
	sscanf(file_contents, "%d", reading);
    return 0;
}


