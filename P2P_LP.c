#include<stdio.h>
#include<stdlib.h>
#include "myerror.h"
#include "menu.h"
#include "myserver.h"

int main(int argc, char *argv[])
{
    int menuReturn, serverActived;

    /*Creates a List of Socket*/
//    socketVector sockList;
//    sockList.qtySockets = 0;
//    sockList.sVector = NULL;

    /* Starts the Background Server */
    if((serverActived = start_Server(PORT)) < 0)
    {
        return ERROR;
    }

    /*Starts the List of Contacts*/
    if(start_Contact_List() != 0)
    {
        return ERROR;
    }

    /* Starts the Menu for user*/
    menuReturn = menu();
    if(menuReturn == ERROR)
    {
        perror("Error");
        return ERROR;
    }


    /*Libera Memória*/
    //if(sockList.sVector != NULL){free(sockList.sVector);}

    return 0;
}
