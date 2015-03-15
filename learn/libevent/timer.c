/*
 * ------------------------------------------------------------------------
 *   File Name: timer.c
 *      Author: Zhao Yanbai
 *              Sat Feb 28 17:03:43 2015
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<event.h>
#include<time.h>
#include<sys/time.h>
#include<stdio.h>

struct event ev;
struct timeval tv;

unsigned int cnt = 0;

void time_cb(int fd, short event, void *argc)
{
    printf("timer woke up %u times\n", cnt++);
    event_add(&ev, &tv);
}

int main()
{
    struct event_base *base = event_init();

    tv.tv_sec = 1;
    tv.tv_usec= 0;

    evtimer_set(&ev, time_cb, NULL);
    event_add(&ev, &tv);

    event_base_dispatch(base);

    return 0;
}
