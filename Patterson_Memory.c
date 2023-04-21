/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and Megan Patterson									*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"


/*
 * adds a new node to a linked list pointed to by head
 */
int add_to_list (row_of_memory** head,
		 short unsigned int address,
		 short unsigned int contents)
{

	row_of_memory = search_address(head, address)
		if (head = NULL) { 
			return (new_row);
			  }

	row_of_memory* new_row = malloc (sizeof (row_of_memory));
	
			new_row-> address =address; 
			new_row-> label =NULL; 
			new_row-> contents = NULL; 
			new_row-> assembly = NULL; 
			new_row -> next = Null; 
		
    /* check to see if there is already an entry for this address and update the contents, if so */
    
    /* allocate memory for a single node */

	/* populate fields in newly allocated node w/ address&contents */

	/* if head==NULL, node created is the new head of the list! */

	/* otherwise, insert node into the list in address ascending order */

	/* return 0 for success, -1 if malloc fails */
	
	
	row_of_memory* head = head; 
	
	while (head-> next < new_row){
		head = head -> next; 
	}
	head-> next = new_row; 
	return 0 ;
}



/*
 * search linked list by address field, returns node if found
 */
row_of_memory* search_address (row_of_memory* head,
			       short unsigned int address )
{
	/* traverse linked list, searching each node for "address"  */

	/* return pointer to node in the list if item is found */

	/* return NULL if list is empty or if "address" isn't found */
	
	while (head ! =NULL && head-> address != address){
		head = head -> next;
		return (*head); 
	}
	
else{
	return NULL ;
}
	
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode  (row_of_memory* head,
				      short unsigned int opcode  ){  
printf("start of search_opcode")
	
// while there is a list that is not empty, and there is a contents node that is not empty, and the assemby row of the node = NULL, return that node. if not index 
	int i =0; 
	char Hold_hex[50];            //array to hold hex characters & #
	while (head != NULL && head -> contents != NULL 
		   && (head -> assembly = NULL) ){ 
				printf(head -> contents);	
				//sprintf (Hold_hex[i], "%x",contents);  //put contents into an array
				//if (Hold_hex [0]==1){
			
				return (&head);  
								// return the row that met the while loop conditions
				head = head-> next;
				}
	printf("end of search_opcode");
	}                              
//}                    //END search_opcode


void print_list(row_of_memory* head) {

    /* make sure head isn't NULL */
    if (head == NULL) {
        printf("Sorry, nothing to print\n");
        return;
    }

    /* print out a header */
    printf("<label>\t<address>\t<contents>\t<assembly>\n");

    /* traverse linked list, print contents of each node */
    row_of_memory* pointer = head;

    while (pointer != NULL) {
        if (pointer->label != NULL) {
            printf("%-20s", pointer->label);
        } else {
            printf("%-20s", "");
        }

        if (pointer->address != NULL) {
            printf("0x%04X\t", pointer->address);
        } else {
            printf("0x0000\t");
        }

        if (pointer->contents != NULL) {
            printf("0x%04X\t\t", pointer->contents);
        } else {
            printf("\t\t\t");
        }

        if (pointer->assembly != NULL) {
            printf("%s\n", pointer->assembly);
        } else {
            printf("\n");
        }

        pointer = pointer->next;
    }
}

/*
 * delete entire linked list
 */

	/* delete entire list node by node */
	/* if no errors, set head = NULL upon deletion */

	/* return 0 if no error, -1 for any errors that may arise */
  
  int delete_list(row_of_memory** head) {


    // check if head is NULL
    if (*head == NULL) {
        return 0;
    }

    row_of_memory* current = *head; // put head at the address start
    while (current != NULL) {  // go through full LL
        row_of_memory* next = current->next; // set next before you delete current
        // free dynamically allocated memory
        free(current->assembly);
        free(current->label);
        free(current);  // free the current-- we have already set current to next so place will not be lost
        current = next;
    }
    *head = NULL; // set the list head pointer to NULL upon deletion
    return 0;
}
	
