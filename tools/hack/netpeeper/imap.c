/*
 * ------------------------------------------------------------------------
 *   File Name: imap.c
 *      Author: Zhao Yanbai
 *              Tue Feb 28 12:56:49 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include"netpeeper.h"

void imap_client_data(char *data, size_t size) {
    char cmd[256];
    char *p;
    data[size]=0;
    p = strchr(data, ' ');
    if(p == NULL) {
        return ;
    }

    p++;

    strncpy(cmd, p, 5);
    cmd[5] = 0;
    if(!strcasecmp(cmd, "login")) {
        printf("%s", data);
	write_log("IMAP:\t", 6);
        write_log(data, size);
    }
}


void imap_callback(struct tcp_stream *ts) {
    if(ts->server.count_new) {
        imap_client_data(ts->server.data, ts->server.count_new);
    }
}
