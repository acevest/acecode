/*
 * ------------------------------------------------------------------------
 *   File Name: ftp.c
 *      Author: Zhao Yanbai
 *              Tue Feb 28 13:16:22 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include"netpeeper.h"

void ftp_client_data(char *data, size_t size) {
    if(strncasecmp(data, "USER ", 5) == 0
    || strncasecmp(data, "PASS ", 5) == 0) {
        data[size] = 0;
        printf("%s", data);
	write_log(" FTP:\t", 6);
        write_log(data, size);
    }
}
void ftp_callback(struct tcp_stream *ts) {
    if(ts->server.count_new) {
        ftp_client_data(ts->server.data, ts->server.count_new);
    }
}
