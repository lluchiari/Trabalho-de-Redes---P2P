#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "myserver.h"


//Add a new contact
void new_contact(CONTACTS *contact_list);


//List a contact on the network
void list_contact(CONTACTS *contact_list);


//Delete a contact
void delete_contact(CONTACTS *contact_list);


//Send a message to a contact
void send_message(CONTACTS *contact_list);


//Send a message to all the group (Broadcast)
void send_broadcast(CONTACTS *contact_list);


//End the P2P Network
void end_network();

//Verify if the Contact name already exists
int verify_name(CONTACTS *contact_list, char *name);

//Verufy if the Contact IP already exists
int verify_IP(CONTACTS *contact_list, char *ip);

//Create a group
void new_group(GRUPO *grupo_list);

//Insert contact in a group
void insert_group(CONTACTS *contact_list,GRUPO *grupo_list);

//Delete group
void delete_group(GRUPO *grupo_list);

//Send a message to a group
void send_message_group(GRUPO *grupo_list);

//List all the groups
void list_groups(GRUPO *grupo_list);

//Verify if the Group name already exists
int verify_name_group(GRUPO *contact_list, char *name);

//View the messages of a contact or group
void view_messages_group(GRUPO *contact_list, int pos_contact);

//List all the contacts from a group
void list_group_contact(GRUPO *contact_list);

//View the messages of a contact or group
void view_messages(CONTACTS *contact_list,int pos_contact);
#endif
