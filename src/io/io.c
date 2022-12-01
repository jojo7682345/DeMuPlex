#include "io.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void getConsoleSize(int* columns, int* lines){
    int cols = 80;
    int lins = 24;

#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    cols = ts.ts_cols;
    lins = ts.ts_lines;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    cols = ts.ws_col;
    lins = ts.ws_row;
#endif /* TIOCGSIZE */

    if(columns){
        *columns = cols;
    }
    if(lines){
        *lines = lins;
    }
}

void printSectionSeparator(const char* style) {
    int width = 0;
    getConsoleSize(&width, NULL);

    char* buff = malloc(width+2);
    memset(buff, 0, width+2);
    buff[width] = '\n';
    
    uint32_t styleLength = strlen(style);
    for(uint32_t i = 0; i < width; i++){
        buff[i] = style[i%styleLength];
    }
    printf(buff);

}

void resetTextColor(){
    printf("\x1B[0m");
}

void textcolor(int attr, int fg, int bg)
{	char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

void printLegend(){

}

uint32_t querryInputI(const char* question){
    printf("%s: ",question);
    uint32_t response = 0;
    scanf("%u",&response);
    return response;
}