#include "myserver.h"

int start_Server(int port)
{
    int i;
    pthread_t masterServerThread;
    pthread_mutex_init(&contactMutex, NULL);

    /*Clears the Socket List*/
    SOCK_VECTOR.qtySockets = 0;
    for(i=0; i<MAX_CONTACT; i++){SOCK_VECTOR.sVector[i] = 0;}

    if(pthread_create(&masterServerThread, NULL, masterServer, &SOCK_VECTOR) < 0)
    {
        perror("Fail Creating Server's Thread");
    }
    if(SERVER_BUG != 0)
    {
        printf("Server Error: Bug $(%d)\n", SERVER_BUG);
        return ERROR;
    }

    /*LOG Register*/
    //puts("Server Actived!");
    return 0;
}

int start_Contact_List()
{
    /******** OPEN FILE AND LIST CONTACTS ********/
    FILE *pFile;
    int i;
    pFile = fopen("Hosts.txt","r");
    if(pFile == NULL)
    {
        printf("Unable to open the file \n");
    }
    else
    {
        for(i=0;i<MAX_CONTACT;i++)
        {
        	contact_list[i].isOnline = 0;
        	if(strcmp(contact_list[i].name, "NULL") == 0)
        	{
                contact_list[i].isOnline = -1;
        	}
        	if(feof(pFile)!=0)
        	{
        		strcpy(contact_list[i].IP,"NULL");
        		strcpy(contact_list[i].name,"NULL");
        		contact_list[i].isOnline = -1;
        	}
            fscanf(pFile, "%s\t%s", contact_list[i].name, contact_list[i].IP);
        }
        fclose(pFile);
    }
	/******* CLOSE FILE *******/
	return 0;
}


void *masterServer(void *socketList)
{
    int sock_desc, new_socket, c, *new_sock, idConected, cHInfo[2];
    char *ipString;
    //socketVector *sockList = (socketVector *) socketList;

    struct sockaddr_in server, client;
    PROTOCOL_MESSAGE *message;

    /* Create a Socket */
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(!sock_desc)
    {
        puts("Could not create socket!");
        SERVER_BUG = SRV_ERROR_SOCK;
        return;
    }

    /* Prepare the sockaddr_in */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    /* Bind */
    printf("Binding.....\n");
    while(bind(sock_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        /*LOG Register*/
        //puts("Bind Failure");
        //printf("Socket error: %d, %s\n", errno, strerror(errno));

        /*Thread Sleep For Wait*/
        sleep(5);
    }

    /*LOG Register*/
    //puts("Bind Done!");

    /* Listen Connections */
    listen(sock_desc, MAX_SERVER_CLIENTS);

    /* Accept and incoming connection */
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while(!SERVER_END)
    {
        if(new_socket = accept(sock_desc, (struct sockaddr *)&client, (socklen_t*)&c))
        {

            ipString = print_ip(client.sin_addr.s_addr);

            /*Verify if the IP is on Contact List*/
            idConected = verify_IP(contact_list, ipString);
            printf("IP Adrees: (%s) | Connected? (%d)\n", ipString, idConected);
            if(idConected != -1)
            {
                //puts("Conection Accepted");

                /* Replies the Client - Welcome Message*/
                message = (PROTOCOL_MESSAGE *)malloc(sizeof(PROTOCOL_MESSAGE));
                message->protocol_type = 1;
                strcpy(message->protocol_message, "Hey Ho. Lets go?");

                write(new_socket, message, sizeof(PROTOCOL_MESSAGE));

                free(message);

                /*Creating the Thread */
                pthread_t sniffer_thread;
                new_sock = malloc(sizeof(int));
                *new_sock = new_socket;

                cHInfo[0] = new_socket;
                cHInfo[1] = idConected;

                if(pthread_create(&sniffer_thread, NULL, connection_handler, (void*) cHInfo) < 0)
                {
                    perror("Could not create thread");
                    SERVER_BUG = SRV_ERROR_THREAD;
                    return;
                }

                //Now join the thread , so that we dont terminate before the thread
                //pthread_join( sniffer_thread , NULL);
                puts("Handler assigned");

                /*Mark as Online User*/
                contact_list[idConected].isOnline = 1;

                /*Inserts the Socket at the SocketList on ID position*/
                SOCK_VECTOR.sVector[idConected] = new_socket;

                SOCK_VECTOR.qtySockets++;




                 //TODO-->Insercao na Lista de Contatos
//                {
//                    if(sockList->qtySockets == 0)
//                    {
//                        sockList->sVector = (int *) malloc(sizeof(int));
//                        sockList->qtySockets++;
//                    }
//                    else
//                    {
//                        sockList->qtySockets++;
//                        sockList->sVector = (int *)realloc(sockList->sVector,sockList->qtySockets*sizeof(int));
//                    }
//                    sockList->sVector[sockList->qtySockets-1] = new_socket;
//                    puts("Caramba........chegou ate aqui!!");
//                    printf("Sock Value: %d\n", sockList->sVector[sockList->qtySockets-1]);
//                }
            }
            /*Connection Refused! Contact isnt in List of Contacts*/
            else
            {
                char REFUSE_CONNECTION_MESSAGE[] = "Connection not Available\n";

                //TODO -> Enquadrar no protocolo de transmissão!//
                write(new_socket, REFUSE_CONNECTION_MESSAGE, sizeof(REFUSE_CONNECTION_MESSAGE));
                close(new_socket);
            }
            free(ipString);
        }
    }

    if(new_socket < 0)
    {
        perror("Accept Failure!\n");
        SERVER_BUG = SRV_ERROR_SOCK;
        return;
    }

    close(new_socket);
    close(sock_desc);

    pthread_exit((void *)0);
    return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    PROTOCOL_MESSAGE client_message;
    int *sockInfo = (int *)socket_desc;
    int read_size;
    char *message;

    int exit_flag = 0;
    //Receive a message from client
    while(exit_flag == 0 && !SERVER_END)
    {
        if((read_size = recv(sockInfo[0] , &client_message , sizeof(PROTOCOL_MESSAGE), 0) > 0))
        {
            /*Writes on the Logs System the message*/
            writeOnLog(sockInfo[1], client_message);

//            if(strstr(client_message.protocol_message, "--exit") != NULL)
//            {
//                char exit_message[] = "Ok, Thanks for cennection\n";
//                write(sockInfo[0], exit_message, strlen(exit_message));
//                /*LOG Register*/
//                //puts("Client disconnected");
//                exit_flag = 1;
//            }

            //Send the message back to client
            //write(sock , client_message , strlen(client_message));

        }
        if(read_size == -1)
        {
            perror("recv failed");
        }
    }

    close(sockInfo[0]);

    /*Mark as Offline User*/
    contact_list[sockInfo[1]].isOnline = 0;

    return 0;
}

char *print_ip(int ip)
{
    char *ipAddr = malloc(16);
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
    sprintf(ipAddr, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
    printf("Uhhhhhhhhhuuu: (%s)\n", ipAddr);
    return ipAddr;
}

int writeOnLog(int pos_contact, PROTOCOL_MESSAGE message)
{
    FILE *pFile;
    char contact[30];

    strcpy(contact,"Logs/");
    strcat(contact,contact_list[pos_contact].name);
    strcat(contact,".txt");

    pFile = fopen(contact,"a");
    if(pFile == NULL){printf("Bug!!\n");}

//    system("clear");
//    view_messages(contact_list, pos_contact);

    //Imprime no Arquivo de Log Local//
    fprintf(pFile, "%s\n",message.protocol_message);
    fclose(pFile);

    return 0;
}

int end_Server()
{
    SERVER_END = 1;
}
