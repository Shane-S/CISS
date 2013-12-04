#ifndef CISS_UTILS_H
#define CISS_UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>

#define INOT_BUF_SIZE sizeof(struct inotify_event) * 16
#define NAME_BUF_SIZE 256

void CISS_delete_file(const char *directory, const char *filename);
void CISS_parse_filename(const char *filename, char *sensor, char *timestamp);
int CISS_read_file(const char *directory, char *filename, int inotifyFd, int *reading);
#endif

