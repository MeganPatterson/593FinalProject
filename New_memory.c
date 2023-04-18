/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>


/*
 * adds a new node to a linked list pointed to by head
 */
int add_to_list (row_of_memory** head,
		 short unsigned int address,
		 short unsigned int contents)
{

	/*
		typedef struct row_of_memory_struct {
			short unsigned int address ;
			char * label ;
			short unsigned int contents ;
			char * assembly ;
			struct row_of_memory_struct *next ;
		} row_of_memory ;
	*/

	// set up current pointers
	row_of_memory* current = *head;
	row_of_memory* currentB = current;

  /* check to see if there is already an entry for this address and update the contents.  no additional steps required in this case */
	current = search_address (*head,address);
	if (current) {
			current->contents = contents;
			return 0;
	}

		
  /* allocate memory for a single node 
	but first check to see if node already exists at address*/
	// first reset current back to the head
	current = *head;
	
	if (current == NULL) {

			current = (row_of_memory*) calloc (1, sizeof(row_of_memory));
			if(current == NULL) return -1;
			current->address = address;
			current->contents = contents;
			*head = current;

	}
	
	else {

		// find appropriate place in linked list to place new node:
		currentB = current;

		//first check if address is smaller than the address on the head node.  If so, create a new head node.
		if (current->address > address) {
				currentB = (row_of_memory*) calloc(1, sizeof(row_of_memory));
				if(currentB == NULL) return -1;
				currentB->address = address;
				currentB->contents = contents;
				currentB->label = NULL;
				currentB->next = current;
				*head = currentB;
				return 0;
		}

		while (current){
				
				if (current->address < address) {
						// address to be placed is the largest, then just add to the end.
						if (current->next == NULL) {
								current->next = (row_of_memory*) calloc(1, sizeof(row_of_memory));
								if(current->next == NULL) return -1;
								current->next->address = address;
								current->next->contents = contents;
								current->next->label = NULL;
								current->next->next = NULL;
								break;
						}
						else {
							currentB = current;
							current = current->next;
						}
				}
				else {
					// appropriate ordered node is in the middle: 
					//now address is next lowest, so node needs to be created here
	/* populate fields in newly allocated node w/ address&contents, NULL for label and assembly */
	/* do not malloc() storage for label and assembly here - do it in parse_file() and reverse_assemble() */
					currentB->next = (row_of_memory*) calloc(1, sizeof(row_of_memory));
					if(currentB->next == NULL) return -1;
					currentB->next->address = address;
					currentB->next->contents = contents;
					currentB->next->label = NULL;
					currentB->next->next = current;
					break;
				}
		}
	}

	/* if *head is NULL, node created is the new head of the list! */

	/* otherwise, insert node into the list in address ascending order */

	/* return 0 for success, -1 if malloc fails */



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

	// create current node and initialize to point to head node
	row_of_memory* current = head;

	// while current node != NULL, traverse linked list and search for address.
	while (current) {
		if (current->address == address) {
			// if address is found, return pointer to node with address = address passed in.
			return current;
		}
		// increment current pointer to next node
		current = current->next;
	}
	//if list is empty, return null
	return NULL ;
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode  (row_of_memory* head,
				      short unsigned int opcode  )
{
    /* opcode parameter is in the least significant 4 bits of the short int and ranges from 0-15 */
		/* see assignment instructions for a detailed description */
    
    /* traverse linked list until node is found with matching opcode in the most significant 4 bits
	   AND "assembly" field of node is NULL */

		// create current node and initialize to point to head node

		/* return pointer to node in the list if item is found */

		/* return NULL if list is empty or if no matching nodes */
		row_of_memory* current = head;

		while (current) {

				if ((opcode == (current->contents >> 12)) && (current->assembly == NULL)) {
						return current;
				}
				else {
						current = current->next;
				}
		}
		return NULL ;
}


void print_list (row_of_memory* head )
{
	/* make sure head isn't NULL */

	/* print out a header */
    
    /* don't print assembly directives for non opcode 1 instructions if you are doing extra credit */

	/* traverse linked list, print contents of each node */

	row_of_memory* current = head;
	int nodeIndex = 2;

		if (head == NULL) {
				printf("You are trying to print with a NULL head node");
				return;
		}
		else {

			printf("1 <label>\t\t<address>\t<contents>\t<assembly>\n");
			while (current) {// same as (current != null) 

			printf("%d %s\t\t%04X\t\t%04X \t\t %s\n",
							nodeIndex, current->label, current->address, current->contents, current->assembly);
					current = current->next;
					nodeIndex++;
			}
		}

	return ;
}

/*
 * delete entire linked list
 */
int delete_list (row_of_memory** head){
	/* delete entire list node by node */
	/* set the list head pointer to NULL upon deletion */
	row_of_memory* current = *head; // put head at the address start
	while (current !=NULL) {  // go through full LL
		row_of_memory* next = current -> next; //set next before you delete current
		if (current ->)
		free(current);
		current = next; 
	}
	*head = NULL; // set the list head pointer to NULL upon deletion
	return 0 ;
}
