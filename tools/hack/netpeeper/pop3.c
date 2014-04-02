/*
 * ------------------------------------------------------------------------
 *   File Name: pop3.c
 *      Author: Zhao Yanbai
 *              Tue Feb 28 10:59:39 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include "netpeeper.h"

void pop3_client_data(char *data, size_t size) {
    if(strncasecmp(data, "USER ", 5) == 0
    || strncasecmp(data, "PASS ", 5) == 0) {
        data[size] = 0;
        printf("%s", data);
	write_log("POP3:\t", 6);
        write_log(data, size);
    }
}

void pop3_callback(struct tcp_stream *ts) {
    if(ts->server.count_new) {
        pop3_client_data(ts->server.data, ts->server.count_new);
    }
}
