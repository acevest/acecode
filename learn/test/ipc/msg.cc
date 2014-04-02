/*
 *--------------------------------------------------------------------------
 *   File Name:	msg.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri Apr 22 16:54:41 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "ipc.h"

using namespace std;

const int MAX_MSG_SIZE	= 256;
const int msg_count = 100;

enum {
	MSG_NORMAL = 1,	// 如果这里设为0,因为recv时候type设为0就只会接收一个数据包
	MSG_EXIT
};

typedef struct _msg_ {
	long	type;
	char	msg[MAX_MSG_SIZE];
} Msg;

void Child(int msgid) {

	int id = msgget(IPC_KEY_MSG, 0);
	if(id == -1) {
		perror("child msgget");
		exit(EXIT_FAILURE);
	}
	assert(id == msgid);

	while(true){
		Msg msg;
		msgrcv(msgid, &msg, sizeof(msg), 0, 0);

		cout<<msg.msg<<"\t"<<msg.type<<endl;

		if(msg.type == MSG_EXIT) break;
	}

}

void Parent(int msgid) {
	srand(time(NULL));
	for(int i=0; i<msg_count; i++) {
		stringstream ss;
		Msg	msg;
		ss<<i<<":"<<rand();
		msg.type = MSG_NORMAL;
		if(i==msg_count-1) msg.type = MSG_EXIT;

		string str = ss.str();
		strcpy(msg.msg, str.c_str());
		msgsnd(msgid, &msg, MAX_MSG_SIZE, 0);
	}

}


int main() {

	int msgid = msgget(IPC_KEY_MSG, IPC_CREAT | IPC_EXCL);
	if(msgid == -1) {
		perror("msgget");
		exit(EXIT_FAILURE);
	}


	int pid = fork();

	if(pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if(pid == 0) {
		Child(msgid);
	} else {
		Parent(msgid);
		wait(NULL);
		msgctl(msgid, IPC_RMID, 0);
	}

	return 0;
}
