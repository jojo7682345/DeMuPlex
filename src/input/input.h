#include <stdint.h>

#define FILE_NAME_MAX 255
#define FILE_PATH_MAX 4096

typedef struct File {
    char name[FILE_NAME_MAX+1];
    char path[FILE_PATH_MAX+1];
    char fullPath[FILE_PATH_MAX+1+FILE_NAME_MAX+1];
}File;

void listFilesInDirectory(const char* path, uint32_t* fileCount, File* files);