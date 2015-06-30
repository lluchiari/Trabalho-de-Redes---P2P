#ifndef MY_SERVER_H
#define MY_SERVER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

#define MAX_SERVER_CLIENTS 100
#define PORT 8888

#define IP_LENGTH 15
#define MAX_CONTACT 30
#define MAX_MSG 140
#define TRY_TIMES 3

typedef struct {
    int qtySockets;
    int sVector[MAX_CONTACT];
} socketVector;

typedef struct {
    int protocol_type;
    char protocol_contacts[MAX_CONTACT][IP_LENGTH+1];           //For Gourp Only//
    char protocol_message[MAX_MSG];
} PROTOCOL_MESSAGE;

typedef struct {

	char name[16];
	char IP[20];
    	int isOnline;
} CONTACTS;

typedef struct {
	char name[16];
	int valid;
} GRUPO;

#include "functions.h"
#include "myerror.h"

int SERVER_BUG;
int SERVER_END;

//Vector of Contacts//
CONTACTS contact_list[MAX_CONTACT];

//Mutex for Multithread Access//
pthread_mutex_t contactMutex;

socketVector SOCK_VECTOR;

/**
*   @description Starts the Main Server for Receive Connections
*   @autor Lluchiari
*   @args A integer containing the Port
*   @return Zero for correct Start or ERROR for error. ERROR can be found on myerror.h
*/
int start_Server(int);

void *connection_handler(void *);
void *masterServer(void *);
char *print_ip(int);
int writeOnLog(int, PROTOCOL_MESSAGE);

#endif
