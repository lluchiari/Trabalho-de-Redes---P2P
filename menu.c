#include "menu.h"

void print_tela()
{
	system("clear");
	printf("\t1- Adicionar Contato\n");
	printf("\t2- Listar contatos\n");
	printf("\t3- Excluir um contato\n");
	printf("\t4- Enviar uma mensagem\n");
	printf("\t5- Mensagem em grupo\n");
	printf("\t6- Sair\n");
}

void print_tela_grupo()
{
	system("clear");
	printf("\t1- Adicionar Grupo\n");
	printf("\t2- Listar Grupo\n");
	printf("\t3- Excluir um Grupo\n");
	printf("\t4- Enviar uma mensagem\n");
	printf("\t5- BROADCAST\n");
	printf("\t6- Inserir no grupo\n");
	printf("\t7- Sair\n");
}

int menu()
{
	int is_end = 0, menu_opt;
	char ip_user[16], ip_sender[16], ip_receiver[16];
	char client_message[2000];

	while(!is_end)
	{
		print_tela();
		scanf("%d", &menu_opt);
		switch(menu_opt){
			case 1:
				new_contact(contact_list);//Add a new contact

			//	is_end = 1; //get out the loop
			break;

			case 2:
				list_contact(contact_list);
				printf("Deseja mandar uma mensagem? [ 1=SIM / 0=NAO ]  ");
				scanf("%d", &menu_opt);
					if(menu_opt)
						printf("Enviando mensagem\n");
				//list_contact(ip_user); //List a contact on the network
			//	is_end = 1; //get out the loop
			break;

			case 3:
				delete_contact(contact_list);

			//	is_end = 1; //get out the loop
			break;

			case 4:
				send_message(contact_list);
			break;

			case 5:
                menu_grupo();
//				send_broadcast(contact_list); //Send a message to all the group (Broadcast)
			//	is_end = 1; //get out the loop
			break;

			case 6:
			//	end_network(); //End the P2P Network
				is_end = 1; //get out the loop
			break;
		}
	}
  return 0;
}

int menu_grupo()
{
	int is_end = 0, menu_opt;
	CONTACTS contact_list[MAX_CONTACT];
	GRUPO grupo_list[MAX_CONTACT];

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

    /******** OPEN FILE AND LIST CONTACTS ********/
    pFile = fopen("Grupos/Grupos.txt","r");
    if(pFile == NULL)
    {
        printf("Unable to open the file \n");
    }
    else
    {
        for(i=0;i<MAX_CONTACT;i++)
        {
        	grupo_list[i].valid = 0;
        	fscanf(pFile, "%s", grupo_list[i].name);
        	if(feof(pFile)!=0)
        	{
        		strcpy(grupo_list[i].name,"NULL");
        		grupo_list[i].valid = -1;
        	}

        }
        fclose(pFile);
    }
	/******* CLOSE FILE *******/

	while(!is_end)
	{
		print_tela_grupo();
		scanf("%d", &menu_opt);
		switch(menu_opt){
			case 1:
				new_group(grupo_list);//Add a new contact


			//	is_end = 1; //get out the loop
			break;

			case 2:
				list_groups(grupo_list);
				printf("Deseja ver algum grupo? [ 1=SIM / 0=NAO ]  ");
				scanf("%d", &menu_opt);
					if(menu_opt == 1)
					{
						list_group_contact(grupo_list);
						printf("Deseja enviar uma mensagem? [ 1=SIM / 0=NAO ]  ");
						scanf("%d", &menu_opt);
						if(menu_opt == 1)
						{
							send_message_group(grupo_list);
						}
					}

				//list_contact(ip_user); //List a contact on the network
			//	is_end = 1; //get out the loop
			break;

			case 3:
				delete_group(grupo_list);

			//	is_end = 1; //get out the loop
			break;

			case 4:
				send_message_group(grupo_list);//Send a message to a group
			//	is_end = 1; //get out the loop
			break;

			case 5:
				send_broadcast(contact_list); //Send a message to all the group (Broadcast)
			//	is_end = 1; //get out the loop
			break;

			case 6:
				insert_group(contact_list,grupo_list); //Send a message to all the group (Broadcast)
			//	is_end = 1; //get out the loop
			break;

			case 7:
			//	end_network(); //End the P2P Network
				is_end = 1; //get out the loop
			break;
		}
	}
  return 0;
}
