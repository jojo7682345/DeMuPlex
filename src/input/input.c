#include "input.h"

#define __USE_MISC
#include <dirent.h>

#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>


void test(const char* directory){
    DIR* dir = opendir(directory);


    closedir(dir);
}

void listFilesInDirectory(const char* path, uint32_t* fileCount, File * files){
    DIR *d = opendir(path);
    struct dirent *dir;
    char full_path[FILE_PATH_MAX];
    *fileCount=0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            //Condition to check regular file.
            if(dir->d_type==DT_LNK){
                full_path[0]='\0';
                strcat(full_path,path);
                strcat(full_path,"/");
                strcat(full_path,dir->d_name);
                
                if(files){
                    uint32_t nameLength = strlen(dir->d_name);
                    memset(files[*fileCount].name, 0, FILE_NAME_MAX+1);
                    memcpy(files[*fileCount].name, dir->d_name, (nameLength<FILE_NAME_MAX)?nameLength:FILE_NAME_MAX);
                    
                    uint32_t pathLength = strlen(path);
                    memset(files[*fileCount].path, 0, FILE_PATH_MAX+1);
                    memcpy(files[*fileCount].path, path, (pathLength<FILE_PATH_MAX)?pathLength:FILE_PATH_MAX);

                    uint32_t fullPathLength = strlen(full_path);
                    memset(files[*fileCount].fullPath, 0, FILE_PATH_MAX+1+FILE_NAME_MAX+1);
                    memcpy(files[*fileCount].fullPath, full_path, (fullPathLength<FILE_PATH_MAX)?fullPathLength:FILE_PATH_MAX);
                }
                *fileCount = (*fileCount)+1;
            }
        }
    }
    //rewinddir(d);
    closedir(d);    
}

