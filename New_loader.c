/************************************************************************/
/* File Name : lc4_loader.c		 										*/
/* Purpose   : This file implements the loader (ld) from PennSim		*/
/*             It will be called by main()								*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>

/* declarations of functions that must defined in lc4_loader.c */

FILE* open_file(char* file_name) {
	FILE* objFile = fopen(file_name, "rb");

	if (!objFile) {
		return NULL;
	}
	return objFile;
}

int parse_file (FILE* my_obj_file, row_of_memory** memory) {
  
/* remember to adjust 16-bit values read from the file for endiannness
 * remember to check return values from fread() and/or fgetc()
  
	from prof, pull in from argv.
 */

 while (1) {

			//check the first header
			//can merge these by getting clever with shifting
			unsigned short int byte1 = fgetc(my_obj_file) ;
			if (feof(my_obj_file)) {break;}
			unsigned short int byte2 = fgetc(my_obj_file) ;
			if (feof(my_obj_file)) {break;}
			//unsigned short int word1 = ((byte1 & 0xff) | (byte2 & 0xff) << 8);
			unsigned short int word1 = ((byte1 & 0xff) << 8 | (byte2 & 0xff));

			byte1 = fgetc(my_obj_file) ;
			if (feof(my_obj_file)) {break;}
			byte2 = fgetc(my_obj_file) ;
			if (feof(my_obj_file)) {break;}
			unsigned short int word2 = ((byte1 & 0xff) << 8 | (byte2 & 0xff));

			byte1 = fgetc(my_obj_file) ;
			if (feof(my_obj_file)) {break;}
			byte2 = fgetc(my_obj_file) ;
			if (feof(my_obj_file)) {break;}
			unsigned short int word3 = ((byte1 & 0xff) << 8 | (byte2 & 0xff));

			/*
			printf("word1: \"0x%X\"\n", word1);
			printf("word2: \"0x%X\"\n", word2);
			printf("word3: \"0x%X\"\n", word3);
			printf("word3: %d\n", word3);
			*/
			unsigned short int word = 0x00;

			// if code block: corresponds to .CODE directive in assembly
			// n-word body comprising the instructions
			if (word1 == 0xCADE) {
					//printf("This is a code section\n");
					for (int i = 0; i < word3; i++) {
							byte1 = fgetc(my_obj_file) ;
							if (feof(my_obj_file)) {break;}
							byte2 = fgetc(my_obj_file) ;
							if (feof(my_obj_file)) {break;}
							word = ((byte1 & 0xff) << 8 | (byte2 & 0xff));

							//printf("New code instruction: \"0x%X\"\n", word);

							add_to_list(memory, word2 + i, word);
					}
					
			}

			// else if data block
			// n-word body comprising the initial data values. This corresponds to the .DATA directive in assembly.
			else if (word1 == 0xDADA) {
					//printf("This is a data section\n");
					for (int i = 0; i < word3; i++) {
							byte1 = fgetc(my_obj_file) ;
							if (feof(my_obj_file)) {break;}
							byte2 = fgetc(my_obj_file) ;
							if (feof(my_obj_file)) {break;}
							word = ((byte1 & 0xff) << 8 | (byte2 & 0xff));
							
							//printf("New code instruction: \"0x%X\"\n", word);

							// add i to the word 2 in order to increment the address for each row
							add_to_list(memory, word2 + i, word);
					}
			}
			// else if symbol string
			// n-character body comprising the symbol string
			// Note, each character in the file is 1 byte, not 2.  
			// There is no null terminator.
			// Each symbol is its own section
			// These are generated when you create labels (such as "END") in assembly.
			else if (word1 == 0xC3B7) {


					//printf("This is a symbol\n");

					//initialize binary array
					//add 1 for the null terminator
					char* ASCII_label = (char*) malloc(word3 + 1);
					if(ASCII_label == NULL) return -1;
					row_of_memory* current = *memory;

					// translate binary into symbol of ASCII chars
					for (int i = 0; i < word3; i++) {
							unsigned short int byte_i = fgetc(my_obj_file);
							char ASCII_char = (char) byte_i;
							ASCII_label[i] = ASCII_char;
					}

					// variable for label check
					int addFound = 0;

					// add the null terminator
					ASCII_label[word3] = '\0';
					//printf("Label: %s\n", ASCII_label);

    			/* check to see if there is already an entry for this address and update the contents.  no additional steps required in this case */
					current = search_address (*memory, word2);
					if (current) {
							current->label = ASCII_label;
							addFound++;
					}

					/*
					Got rid of the below code to instead use the newly created and required "search address" helper function
					while (current) {
							if (current->address == word2) {
									current->label = ASCII_label;
									addFound ++;
									break;
							}
					current = current->next;
					}
					*/


					// reset current to point to head node
					//current = *memory;

					// if addFound still zero, then a node with symbol's address has not yet been created, so add node
					if (addFound == 0) {
							//reset current to head
							current = *memory;
							//no nodes yet exist
							if (current == NULL) {
									current = (row_of_memory*) calloc (1, sizeof(row_of_memory));
									if(current == NULL) return -1;
									current->label = ASCII_label;
									*memory = current;
							}
							//at least 1 node exists already
							else {
									//add node to the appropriate place in the linked list and add the label, then set all else to NULL.
									//create another pointer
									row_of_memory* currentB = current;

									// if address of head node is larger than the symbol address, need to make a new head node at the symbol address
									if (current->address > word2) {
											currentB = (row_of_memory*) calloc(1, sizeof(row_of_memory));
											if(currentB == NULL) return -1;
											currentB->address = word2;
											currentB->label = ASCII_label;
											currentB->next = current;
											*memory = currentB;
									}

									while (current) {

											if(current->address < word2){
													// if address to be added is largest of all addresses, need to add node at the end
													if (current->next == NULL){
															current->next = (row_of_memory*) calloc(1, sizeof(row_of_memory));
															if(current->next == NULL) return -1;
															current->next->address = word2;
															current->next->label = ASCII_label;
															current->next->next = NULL;
															break;
													}
													
											}
											else {
												// now address is next lowest, so node needs to be created here
												currentB->next = (row_of_memory*) calloc(1, sizeof(row_of_memory));
												if(currentB->next == NULL) return -1;
												currentB->next->address = word2;
												currentB->next->label = ASCII_label;
												currentB->next->next = current;
												break;
											}
											//increment both currentB and current
											currentB = current;
											current = current->next;
									}
							}
					}
			}
			else {
				//printf("Parsed header not one of CADE, DADA, or C3B7\n");
				break;
			}

			// check if the end of the file has been reached.  If so, break. If not, move on.
			if (feof(my_obj_file)) {
					//end of the file reached
					break;
			}
		
 	}
	
	fclose(my_obj_file);
	return 0 ;
}
