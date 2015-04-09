/*
 * ------------------------------------------------------------------------
 *   File Name: main.c
 *      Author: Zhao Yanbai
 *              Mon Feb 27 15:33:43 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<stdio.h>
#include<stdlib.h>
#include"netpeeper.h"

void am_callback(char *data, size_t size) {
    int i;
    int n = size;
    data[size] = 0;
    printf("AM:%s\n", data);
    if(data[0] == 'L' && data[1] == 'G' && data[2] == 'I') {
#if 0
        for(i=0; i<size; i++) {
            if(data[i] == '\n') {
                n = i + 1;
                break;
            }
        }
#endif
        write_log(data, n);
    } else if(data[0] == 'U' && data[1] == 'S' && data[2] == 'R') {
        int count = 0;
        char *p = NULL;
        for(i=0; i<size; i++) {
            if(data[i] == ' ') {
                count++;
            }

            if(count == 3) {
                p = data + i + 1;
                if(*p == 'S') {
                    write_log(data, size);
                }
                break;
            }
        }
    }
}

void tcp_callback(struct tcp_stream *ts, void **arg) {
    if(ts->nids_state == NIDS_JUST_EST) {
        ts->client.collect = 1;
        ts->server.collect = 1;
    }

    if(ts->nids_state != NIDS_DATA) {
        return;
    }
    printf("%d\n", ts->addr.dest);
    switch(ts->addr.dest) {
    case 80:
    case 8080:
        //break;
        printf("data\n");
        http_callback(ts);
        break;
    case 110:
        pop3_callback(ts);
        break;
    case 143:
        imap_callback(ts);
        break;
    case 21:
        ftp_callback(ts);
        break;
    case 5001:
        am_callback(ts->server.data, ts->server.count_new);
        break;
    default:

        break;
    }
}

void usage(const char *app)
{
    printf("Usage:\n\t%s <interface>\n", app);
}

int main(int argc, char *argv[]){

    if(argc != 2)
    {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    nids_params.device = argv[1];
    nids_params.promisc = 1;

    printf("init....\n");
    nids_init();

    printf("register tcp....\n");
    nids_register_tcp(tcp_callback);

    printf("nids run....\n");
    nids_run();

    printf("exit....\n");
	return 0;
}
