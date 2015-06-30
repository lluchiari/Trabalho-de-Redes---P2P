#include"functions.h"


//Add a new contact
void new_contact(CONTACTS *contact_list){
    FILE *pFile;
    int i, j, aux = 0;
    char sAux[20];
    pFile = fopen("Hosts.txt","w");

    if(pFile != NULL)
    {
        for(i=0;i<MAX_CONTACT;i++)
        {
            if(contact_list[i].isOnline == -1)
            {

                while(aux != -1)
                {
                    printf("Write Name (NO SPACES): ");
                    scanf("%s",&sAux);
                    aux = verify_name(contact_list,sAux);
                    /*****Verificação de IP na lista*****/
                    if( aux!= -1)
                    {
                        printf("Este nome já está em seus contatos\n");
                        strcpy(contact_list[i].name," ");
                    }
                    else
                    {
                        strcpy(contact_list[i].name, sAux);
                    }
                }
                aux = 0;
                /****Se não estiver na lista, inserir****/


                /****** Após trocar gets por scanf, nao precisa verificar espaços
                while(strchr(contact_list[i].name,' ')||contact_list[i].name[0]== '\0')
                {
                    printf("Rewrite the Name without space: ");
                    scanf("%s",&sAux);
                    *****Verificação de IP na lista*****
                    if(verify_name(contact_list,sAux) != 0)
                    {
                        printf("Este nome já está em seus contatos\n");
                        strcpy(contact_list[i].name," ");
                    }
                    else
                    {
                        strcpy(contact_list[i].name, sAux);
                    }
                    ****Se não estiver na lista, inserir****
                }
                *******/
                while(aux != -1)
                {
                    printf("\nWrite IP(NO SPACES): ");
                    scanf("%s",&sAux);
                    aux = verify_IP(contact_list,sAux);
                    /*****Verificação de IP na lista*****/
                    if(aux != -1)
                    {
                        printf("Este IP já está em seus contatos\n");
                        strcpy(contact_list[i].IP," ");
                    }
                    else
                    {
                         strcpy(contact_list[i].IP, sAux);
                    }
                }
                /****Se não estiver na lista, inserir****/


                /****** Após trocar gets por scanf, nao precisa verificar espaços
                while(strchr(contact_list[i].IP,' ')||contact_list[i].IP[0]== '\0')
                {
                    printf("Rewrite the IP without space: ");
                    scanf("%s",&sAux);
                    *****Verificação de IP na lista*****
                    if(verify_IP(contact_list,sAux) != 0)
                    {
                        printf("Este IP já está em seus contatos\n");
                        strcpy(contact_list[i].IP," ");
                    }
                    else
                    {
                     strcpy(contact_list[i].IP, sAux);
                    }
                    ****Se não estiver na lista, inserir****
                }
                */

                contact_list[i].isOnline = 0;
                printf("Deseja adicionar mais um contato? [ 1=SIM / 0=NAO ]  ");
                scanf("%d", &aux);
                if(aux == 0)
                {
                    break;
                }
            }

        }
        for(i=0;i<MAX_CONTACT;i++)
        {
            if(!strcmp(contact_list[i].name, "NULL") && !strcmp(contact_list[i].IP, "NULL"))
            {
                continue;
            }
            else if(i == 0)
            {
                fprintf(pFile,"%s\t%s",contact_list[i].name,contact_list[i].IP);
            }
            else{
                fprintf(pFile,"\n%s\t%s",contact_list[i].name,contact_list[i].IP);
            }
        }
        fclose(pFile);
    }
    else
    {
        printf("Could not open file\n");
    }
}

/*###############################################################################################################*/
//List a contact on the network
void list_contact(CONTACTS *contact_list){
    int i;
    printf( "******************************************************************\n"
            "** Nro\t**      NOME\t**         IP\t\t**   ONLINE?\t**\n"
            "******************************************************************\n");
    for(i=0;i<MAX_CONTACT;i++)
        {
            printf("**%3d\t**%10s\t**%18s\t**%7d\t**\n",i, contact_list[i].name, contact_list[i].IP, contact_list[i].isOnline);
        }
    printf("******************************************************************\n");
}

/*###############################################################################################################*/
//Delete a contact
void delete_contact(CONTACTS *contact_list){
    FILE *pFile;
    int i,aux=0, loop = 1;
    char sAux[20];
    pFile = fopen("Hosts.txt","w");


    if(pFile != NULL)
    {
        while(loop == 1)
        {
            printf("Como deseja buscar o contato? [Nome = 0/ IP = 1]\n");
            scanf("%d",&aux);
            if(aux == 0)
            {
                printf("Digite o nome do contato a ser deletado:  ");
                scanf("%s",&sAux);
                i = verify_name(contact_list,sAux);
                if(i != -1){
                    strcpy(contact_list[i].name, "NULL");
                    strcpy(contact_list[i].IP, "NULL");
                    contact_list[i].isOnline = -1;
                    printf("Contato deletado!\n");
                }
            }

            else
            {
                printf("Digite o IP do contato a ser deletado:  ");
                scanf("%s",&sAux);
                i = verify_IP(contact_list,sAux);
                if(i != -1){
                    strcpy(contact_list[i].name, "NULL");
                    strcpy(contact_list[i].IP, "NULL");
                    contact_list[i].isOnline = -1;
                    printf("Contato deletado!\n");
                }
            }
            if(i==-1)
                printf("Contato não existe!\n");

            printf("Deseja deletar mais um contato? [ 1=SIM / 0=NAO ]  ");
                    scanf("%d", &loop);
        }
        for(i=0;i<MAX_CONTACT;i++)
        {
            if(!strcmp(contact_list[i].name, "NULL") && !strcmp(contact_list[i].IP, "NULL"))
            {
                continue;
            }
            else if(i == 0)
            {
                fprintf(pFile,"%s\t%s",contact_list[i].name,contact_list[i].IP);
            }
            else{
                fprintf(pFile,"\n%s\t%s",contact_list[i].name,contact_list[i].IP);
            }
        }
        fprintf(pFile,"\0");

        fclose(pFile);
    }
    else
    {
        printf("Could not open file\n");
    }
}

/*###############################################################################################################*/
//Send a message to a contact
void send_message(CONTACTS *contact_list)
{
    FILE *pFile;
    char msg[141], msg_aux[141], contact[30],c;
    int i, pos_contact, loop=1;
    time_t rawtime;
    struct tm * timeinfo;

     //Try Connect And Send//
    int sock_desc;
    struct sockaddr_in server;
    char *message, server_reply[2000];

    //Lista contatos//
    list_contact(contact_list);

    //Segundo tabela de Indices --> Qual contato referente//
    printf("Qual contato (Nro) você deseja mandar mensagem?  ");
    scanf("%d", &pos_contact);

    if(pos_contact != -1 && pos_contact < MAX_CONTACT)
    {
        //Concatena o o PATH do arquivo com o nome do usuário selecionado//
        strcpy(contact,"Logs/");
        strcat(contact,contact_list[pos_contact].name);
        strcat(contact,".txt");


        while(loop ==1)
        {
            pFile = fopen(contact,"a");
            strcpy(msg, "\0");
            system("clear");
            view_messages(contact_list, pos_contact);
            printf("\nDigite sua mensagem ('--exit' para sair):  ");
            //scanf("%s",msg);
            while(msg[0]=='\0')
            {
                gets(msg);
            }

            if(strcmp(msg, "--exit") == 0)
            {
                loop = 0;
                fclose(pFile);
                break;
            }
            //if(fscanf(stdin,"%s",msg)==EOF){}
            //printf("%s\n",msg );

            time (&rawtime);
            timeinfo = localtime (&rawtime);

            //Imprime no Arquivo de Log Local//
            fprintf(pFile, "[%d/%d/%d %d:%d:%d Para-> %s] %s\n",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,contact_list[pos_contact].name, msg);
            fclose(pFile);

            //***************************************************************************//
            //Creates the massage//
            PROTOCOL_MESSAGE *message;
            message = (PROTOCOL_MESSAGE *)malloc(sizeof(PROTOCOL_MESSAGE));

            //Type of the Message => 1 if is individual message ; 2 if is Group message.
            message->protocol_type = 1;

            //Imprime na String da Mensagem//
            sprintf(message->protocol_message, "[%d/%d/%d %d:%d:%d Para-> %s] %s\n",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,contact_list[pos_contact].name, msg);

            if(contact_list[pos_contact].isOnline)
            {
                printf("Sending Message\n");
                write(SOCK_VECTOR.sVector[pos_contact], message, sizeof(PROTOCOL_MESSAGE));
            }
            else
            {
                printf("Creating Socket\n");

                /*Creating Socket*/
                sock_desc = socket(AF_INET, SOCK_STREAM, 0);
                if(!sock_desc)                                       //Bug
                {
                    printf("Could Not Create Socket\n");
                }
                SOCK_VECTOR.sVector[pos_contact] = sock_desc;

                /* Configuring Struct */
                server.sin_addr.s_addr = inet_addr(contact_list[pos_contact].IP);       //Looks IP Addres from Google
                server.sin_family = AF_INET;
                server.sin_port = htons(PORT);

                //Conect to Remote Server//
                for(i=0; i<TRY_TIMES; i++)
                {
                    if(connect(sock_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
                    {
                        printf("Connect Error\n");
                    }
                    else
                    {
                        write(SOCK_VECTOR.sVector[pos_contact], message, sizeof(PROTOCOL_MESSAGE));
                        contact_list[pos_contact].isOnline = 1;
                        break;
                    }
                }
            }

            //clientSendMessage()
            free (message);

            //***************************************************************************//
        }

    }
    else
    {
        printf("Este contato não existe");
    }
}

/*###############################################################################################################*/
//Send a message to all the group (Broadcast)
void send_broadcast(CONTACTS *contact_list){
    FILE *pFile;
    char msg[141], msg_aux[141], contact[30],c;
    int i, pos_contact, loop = 1;
    time_t rawtime;
    struct tm * timeinfo;

    system("clear");
    while(loop ==1)
    {
        strcpy(msg, "\0");
        printf("Digite sua mensagem ('--exit' para sair):  ");
        while(msg[0]=='\0')
            {
                gets(msg);
            }
        if(strcmp(msg, "--exit") == 0)
        {
            loop = 0;
        }

        for(i=0; i<MAX_CONTACT; i++)
        {
            if(contact_list[i].isOnline != -1)
            {
                strcpy(contact,"Logs/");
                strcat(contact,contact_list[i].name);
                strcat(contact,".txt");
                pFile = fopen(contact,"a");

                if(pFile != NULL)
                {
                    if(loop == 1){
                        time (&rawtime);
                        timeinfo = localtime (&rawtime);
                        fprintf(pFile, "[%d/%d/%d %d:%d:%d (BROADCAST)] %s\n",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, msg);
                    }
                    fclose(pFile);
                }
                else
                {
                    printf("Este contato não existe");
                }
            }
        }
    }
}

/*###############################################################################################################*/
//End the P2P Network
void end_network(){
    printf("This function is working! (end_network())\n");
}
/*###############################################################################################################*/
//Verify if the Contact name already exists
int verify_name(CONTACTS *contact_list, char *name){
    int i;
    printf("ENTROU AQUI ó\n");
    for(i=0;i < MAX_CONTACT;i++)
    {
        if(strcmp(contact_list[i].name,name) == 0)
            return i;
    }
    return -1;
}
/*###############################################################################################################*/
//Verufy if the Contact IP already exists
int verify_IP(CONTACTS *contact_list, char *ip){
    int i;

    for(i=0;i < MAX_CONTACT;i++)
    {
        if(strcmp(contact_list[i].IP,ip) == 0)
        {
            return i;
        }

    }
    return -1;
}
/*###############################################################################################################*/
//Create a group
void new_group(GRUPO *grupo_list){
    FILE *pFile;
    int i, j, aux = 0;
    char sAux[20];
    pFile = fopen("Grupos/Grupos.txt","w");


    if(pFile != NULL)
    {
        for(i=0;i<MAX_CONTACT;i++)
        {
            if(grupo_list[i].valid == -1)
            {
                /* Abre o FILE de Grupos e se não tiver um grupo com o mesmo nome, insere no vetor*/
                while(aux != -1)
                {
                    printf("Write Group Name (NO SPACES): ");
                    scanf("%s",&sAux);
                    aux = verify_name_group(grupo_list,sAux);
                    /*****Verificação de GRUPO na lista*****/
                    if( aux!= -1)
                    {
                        printf("Este grupo já está em seus contatos\n");
                    }
                    else
                    {
                        strcpy(grupo_list[i].name, sAux);
                        grupo_list[i].valid = 0;
                    }
                }
                aux = 0;
                /****Se não estiver na lista, inserir****/

                printf("Deseja criar mais um grupo? [ 1=SIM / 0=NAO ]  ");
                scanf("%d", &aux);
                if(aux == 0)
                {
                    break;
                }
            }
        }
        /*Imprime o Vetor que contem a lista de grupos no FILE*/
        for(i=0;i<MAX_CONTACT;i++)
        {
            if(!strcmp(grupo_list[i].name, "NULL"))
            {
                continue;
            }
            else if(i == 0)
            {
                fprintf(pFile,"%s",grupo_list[i].name);
            }
            else{
                fprintf(pFile,"\n%s",grupo_list[i].name);
            }
        }
        fclose(pFile);
    }
    else
    {
        printf("Could not open file\n");
    }
}
/*###############################################################################################################*/
//Insert contact in a group
void insert_group(CONTACTS *contact_list,GRUPO *grupo_list){
    FILE *pFile;
    CONTACTS contact_group[MAX_CONTACT];
    int pos_group,pos_contact, i,j, aux = 0;
    char contact[30];



    list_groups(grupo_list);
    printf("Qual Grupo (Nro) você deseja mandar mensagem?  ");
    scanf("%d", &pos_group);

    strcpy(contact,"Grupos/");
    strcat(contact,grupo_list[pos_group].name);
    strcat(contact,".txt");

    pFile = fopen(contact,"w");

    list_contact(contact_list);
    if(pFile != NULL)
    {
        for(i=0;i<MAX_CONTACT;i++)
        {
                while(aux != -1)
                {
                    printf("Qual contato (Nro) você adicionar ao grupo?  ");
                    scanf("%d",&pos_contact);
                    aux = verify_name(contact_group,contact_list[pos_contact].name);
                    /*****Verificação de IP na lista*****/
                    if( aux!= -1)
                    {
                        printf("Este nome já está em seus contatos\n");
                        strcpy(contact_group[i].name," ");
                    }
                    else
                    {
                        strcpy(contact_group[i].name, contact_list[pos_contact].name);
                    }
                }
                aux = 0;
                /****Se não estiver na lista, inserir****/

                while(aux != -1)
                {
                    aux = verify_IP(contact_group,contact_list[pos_contact].IP);
                    /*****Verificação de IP na lista*****/
                    if(aux != -1)
                    {
                        printf("Este IP já está em seus contatos\n");
                        strcpy(contact_group[i].IP," ");
                    }
                    else
                    {
                         strcpy(contact_group[i].IP, contact_list[pos_contact].IP);
                    }
                }
                /****Se não estiver na lista, inserir****/

                contact_list[i].isOnline = 0;
                printf("Deseja adicionar mais um contato? [ 1=SIM / 0=NAO ]  ");
                scanf("%d", &aux);
                if(aux == 0)
                {
                    break;
                }
        }
        j = i;
        for(i=0;i<j+1;i++)
        {
            if(i == 0)
            {
                fprintf(pFile,"%s\t%s",contact_group[i].name,contact_group[i].IP);
            }
            else{
                fprintf(pFile,"\n%s\t%s",contact_group[i].name,contact_group[i].IP);
            }
        }
        fclose(pFile);
    }
    else
    {
        printf("Could not open file\n");
    }


}
/*###############################################################################################################*/
//Delete group
void delete_group(GRUPO *grupo_list){
    FILE *pFile;
    int i, loop = 1, pos_group;
    pFile = fopen("Grupos/Grupos.txt","w");

    list_groups(grupo_list);

    if(pFile != NULL)
    {
        while(loop == 1)
        {
            printf("Qual Grupo (Nro) você deseja deletar?  ");
            scanf("%d", &pos_group);

            //i = verify_name_group(grupo_list,grupo_list[pos_group].name);
            if(grupo_list[pos_group].valid != -1){
                strcpy(grupo_list[pos_group].name, "NULL");
                grupo_list[pos_group].valid = -1;
                printf("Contato deletado!\n");
            }


            else
            {
                printf("Contato não existe!\n");
            }

            printf("Deseja deletar mais um contato? [ 1=SIM / 0=NAO ]  ");
            scanf("%d", &loop);
        }
        for(i=0;i<MAX_CONTACT;i++)
        {
            if(!strcmp(grupo_list[i].name, "NULL"))
            {
                continue;
            }
            else if(i == 0)
            {
                fprintf(pFile,"%s",grupo_list[i].name);
            }
            else{
                fprintf(pFile,"\n%s",grupo_list[i].name);
            }
        }
        fprintf(pFile,"\0");

        fclose(pFile);
    }
    else
    {
        printf("Could not open file\n");
    }

}
/*###############################################################################################################*/
//Send a message to a group
void send_message_group(GRUPO *grupo_list){
    FILE *pFile;
    char msg[MAX_MSG], contact[30],c;
    int i, pos_contact, loop=1;
    time_t rawtime;
    struct tm * timeinfo;

    list_groups(grupo_list);
    printf("Qual grupo (Nro) você deseja mandar mensagem?  ");
    scanf("%d", &pos_contact);

    if(grupo_list[pos_contact].valid != -1)
    {

        /* Teste para ver se o grupo possui algum contato*/
        strcpy(contact,"Grupos/");
        strcat(contact,grupo_list[pos_contact].name);
        strcat(contact,".txt");
        pFile = fopen(contact,"r");
        if(pFile != NULL)
        {
            fclose(pFile);
            /* Visto que não está vazio, eu fecho o arquivo para abrir seu Log*/
            strcpy(contact,"Grupos/Logs/");
            strcat(contact,grupo_list[pos_contact].name);
            strcat(contact,".txt");


            while(loop ==1)
            {
                pFile = fopen(contact,"a");
                strcpy(msg, "\0");
                system("clear");
                view_messages_group(grupo_list, pos_contact);
                printf("\nDigite sua mensagem ('--exit' para sair):  ");

                while(msg[0]=='\0')
                {
                    gets(msg);
                }

                if(strcmp(msg, "--exit") == 0)
                {
                    loop = 0;
                    fclose(pFile);
                    break;
                }

                time (&rawtime);
                timeinfo = localtime (&rawtime);
                fprintf(pFile, "[%d/%d/%d %d:%d:%d EU para-> %s] %s\n",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,grupo_list[pos_contact].name, msg);
                fclose(pFile);
            }
        }
        else
        {
            printf("Este grupo não existe\n");
        }
    }
    else
    {
        printf("Este grupo não existe\n");
    }

}

/*###############################################################################################################*/
//List all the groups
void list_groups(GRUPO *grupo_list){
    int i;
    printf( "******************************************************************\n"
            "** Nro\t**      NOME\t**            VALID?\t**\n"
            "******************************************************************\n");
    for(i=0;i<MAX_CONTACT;i++)
        {
            printf("**%3d\t**%10s\t**%3d\t\n",i, grupo_list[i].name, grupo_list[i].valid);
        }
    printf("******************************************************************\n");
}
/*###############################################################################################################*/
//Verify if the Contact name already exists
int verify_name_group(GRUPO *contact_list, char *name){
    int i;

    for(i=0;i < MAX_CONTACT;i++)
    {
        if(strcmp(contact_list[i].name,name) == 0)
            return i;
    }
    return -1;
}
/*###############################################################################################################*/
//View the messages of a contact or group
void view_messages_group(GRUPO *contact_list, int pos_contact){
    FILE *pFile;
    int aux;
    char contact[30],c;

    strcpy(contact,"Grupos/Logs/");
    strcat(contact,contact_list[pos_contact].name);
    strcat(contact,".txt");
    pFile = fopen(contact,"r");

    if(pFile != NULL)
    {
        system("clear");
        while ((c = getc(pFile)) != EOF)
            putchar(c);

        fclose(pFile);
    }
    else
    {
        printf("Este contato não existe");
    }
}
/*###############################################################################################################*/
//List all the contacts from a group
void list_group_contact(GRUPO *grupo_list){
    FILE *pFile;
    CONTACTS contact_group[MAX_CONTACT];
    int pos_group,pos_contact, i,j, aux = 0;
    char contact[30];

    system("clear");
    list_groups(grupo_list);
    printf("Qual Grupo (Nro) você deseja mandar mensagem?  ");
    scanf("%d", &pos_group);

    strcpy(contact,"Grupos/");
    strcat(contact,grupo_list[pos_group].name);
    strcat(contact,".txt");

        /******** OPEN FILE AND LIST CONTACTS ********/
    pFile = fopen(contact,"r");
    if(pFile == NULL)
    {
        printf("Unable to open the file \n");
        printf("GRUPO VAZIO!\n");
    }
    else
    {
        for(i=0;i<MAX_CONTACT;i++)
        {
            contact_group[i].isOnline = 0;
            if(feof(pFile)!=0)
            {
                strcpy(contact_group[i].IP,"NULL");
                strcpy(contact_group[i].name,"NULL");
                contact_group[i].isOnline = -1;
            }
            fscanf(pFile, "%s\t%s", contact_group[i].IP, contact_group[i].name);
        }
        fclose(pFile);

    /******* CLOSE FILE *******/
    list_contact(contact_group);
    }
}

/*###############################################################################################################*/
//View the messages of a contact or group
void view_messages(CONTACTS *contact_list, int pos_contact){
    FILE *pFile;
    int aux;
    char contact[30],c;

    strcpy(contact,"Logs/");
    strcat(contact,contact_list[pos_contact].name);
    strcat(contact,".txt");
    pFile = fopen(contact,"r");

    if(pFile != NULL)
    {
        system("clear");
        while ((c = getc(pFile)) != EOF)
            putchar(c);

        fclose(pFile);
    }
    else
    {
        printf("Este contato não existe");
    }
}
