#include <stdio.h>
#include "io/io.h"
#include "input/input.h"
#include <stdlib.h>
#include <string.h>

int main(){
    
    printSectionSeparator("-");

    const char* path = "/dev/input/by-id/";

    uint32_t fileCount = 0;
    listFilesInDirectory(path,&fileCount,NULL);
    File* files = (File*) malloc(sizeof(File)*fileCount);
    memset(files,0,sizeof(File)*fileCount);
    listFilesInDirectory(path,&fileCount,files);

    //select mouse
    for(uint32_t i = 0; i < fileCount; i++){
        
        if(strstr(files[i].name,"-event-mouse")){
            textcolor(BRIGHT,WHITE,BLACK);
            printf("(%i) = %s", i, files[i].name);
            textcolor(BRIGHT,GREEN,BLACK);
            printf(" **Recommended**");
            
        }else{
            textcolor(DIM,WHITE,BLACK);
            printf("(%i) = %s", i, files[i].name);
        }
        resetTextColor();
        printf("\n");
        
    }

    printSectionSeparator("-");

    printf("%i\n",querryInputI("Select which mouse to use"));

    printSectionSeparator("-");

    //select keyboard
    for(uint32_t i = 0; i < fileCount; i++){

        if(strstr(files[i].name,"-event-if")){
            textcolor(BRIGHT,WHITE,BLACK);
            printf("(%i) = %s", i, files[i].name);
            textcolor(BRIGHT,GREEN,BLACK);
            printf(" **Recommended**");
            
        }else{
            textcolor(DIM,WHITE,BLACK);
            printf("(%i) = %s", i, files[i].name);
        }
        resetTextColor();
        printf("\n");
        
    }

    printSectionSeparator("-");

    printf("%i\n",querryInputI("Select which keyboard to use"));

    return 0;
}