#ifndef FILE_H
#define FILE_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define FILENAME_MAX_LEN 200

void file_expandPath(char *path);
void file_remExtension(char *pathname);
void file_getOpFileName(char *dest, const char* inpfname);
#endif
