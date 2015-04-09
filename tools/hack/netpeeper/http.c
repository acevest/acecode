/*
 * ------------------------------------------------------------------------
 *   File Name: http.c
 *      Author: Zhao Yanbai
 *              Tue Feb 28 10:59:33 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include "netpeeper.h"

void http_client_data(char *data, size_t size, struct tcp_stream *ts) {
    data[size] = 0;
    write_log(data, size);
    return;
#define S(s) {s, (sizeof(s)-1)}
struct item {
    const char *s;
    size_t size;
};
    int i,j;
    static struct item fea[] = {
        S("POST /ajaxLogin/login HTTP/1.1"),            // renren.com
        S("GET /ajax/accounthandler.ashx?t=log")        // csdn.net
    };

    int items = sizeof(fea)/sizeof(struct item);
    
    for(i=0; i<items; i++) {
        if(ts->server.collect==2 || strncmp(data, fea[i].s, fea[i].size) == 0) {
            ts->server.collect = ts->server.collect == 2 ? 1 : 2;
            data[size] = 0;
            printf("%s\n", data);
            write_log(data, size);
            break;      
        }
    }
#undef S
}

void http_callback(struct tcp_stream *ts) {

    int i;

    printf("sssss\n");

    // data receive from client
    if(ts->server.count_new) {
        printf("HTTP FROM Client\n");
        printf("%s\n", ts->server.data);
        http_client_data(ts->server.data, ts->server.count_new, ts);
    }

    //  data receive from server
    if(ts->client.count_new) {
        // discard
    }

}
