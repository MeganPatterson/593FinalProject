/************************************************************************/
/* File Name : lc4.c 													*/
/* Purpose   : This file contains the main() for this project			*/
/*             main() will call the loader and disassembler functions	*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"
#include <string.h>

/* program to mimic pennsim loader and disassemble object files */

int main (int argc, char** argv) {
  
/* leave plenty of room for the filename */
  
  char filename[100];

	/**
	 * main() holds the linked list &
	 * only calls functions in other files
	 */

	/* step 1: create head pointer to linked list: memory 	*/
	/* do not change this line - there should no be malloc calls in main() */
	
	row_of_memory* memory = NULL ;


	/* step 2: determine filename, then open it		*/
	/*   TODO: extract filename from argv, pass it to open_file() */
	if (argc < 2) { 
		printf ("error1: usage: ./lc4 <object_file.obj>\n"); 
		return 1;
	}
	
	//printf ("argv[1]=\"%s\"\n", argv[1]);

//set filename to first argument passed into command line
//since filename is a 100 character array, need to copy in the command line argv[1] into it.
//first initialize filename array to null:
for (int i = 0; i < 100; i++) {
	filename[i] = '\0';
}

//then add a null termator on the end.
	strcpy(filename, argv[1]);

//check filename
/*
for (int i = 0; i < 100; i++) {
	printf("%c", filename[i]);
}
printf("\n");
*/

	FILE* objFile = open_file(filename);
	//REMEMBER TO CLOSE OBJFILE!

	if (objFile == NULL){
		printf ("error1: usage: ./lc4 <object_file.obj>\n"); 
		return 1;
	}


	/* step 3: call function: parse_file() in lc4_loader.c 	*/
	/*   TODO: call function & check for errors		*/

	parse_file (objFile, &memory);

		//from prof, in this function, we will parse file from argv


	/* step 4: call function: reverse_assemble() in lc4_disassembler.c */
	/*   TODO: call function & check for errors		*/
	reverse_assemble (memory);

	/* step 5: call function: print_list() in lc4_memory.c 	*/
	/*   TODO: call function 				*/
	print_list(memory);

	/* step 6: call function: delete_list() in lc4_memory.c */
	/*   TODO: call function & check for errors		*/
	delete_list (&memory);

	/* only return 0 if everything works properly */
	print_list(memory);
	return 0 ;
}
