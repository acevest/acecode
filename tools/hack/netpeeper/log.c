/*
 * ------------------------------------------------------------------------
 *   File Name: log.c
 *      Author: Zhao Yanbai
 *              Tue Feb 28 12:29:02 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include"netpeeper.h"
void write_log(char *data, size_t size) {
    int fd = open("./log.txt", O_APPEND | O_CREAT | O_WRONLY, 0644);
    if(fd == -1) {
       fprintf(stderr, "Cannot open log file...\n");
       return ;
    }
    
    write(fd, data, size);

    close(fd);
}
