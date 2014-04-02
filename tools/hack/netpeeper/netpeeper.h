/*
 * ------------------------------------------------------------------------
 *   File Name: netpeeper.h
 *      Author: Zhao Yanbai
 *              Tue Feb 28 11:02:31 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#ifndef  __H_NETPEEPER_H__
#define  __H_NETPEEPER_H__

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<nids.h>
#include<fcntl.h>

void http_callback(struct tcp_stream *ts);
void pop3_callback(struct tcp_stream *ts);
void imap_callback(struct tcp_stream *ts);
void ftp_callback(struct tcp_stream *ts);


void write_log(char *data, size_t size);
int is_cmd(char *data, size_t size);


#endif /*__H_NETPEEPER_H__*/
