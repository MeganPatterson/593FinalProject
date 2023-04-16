/************************************************************************/
/* File Name : lc4_disassembler.c 										*/
/* Purpose   : This file implements the reverse assembler 				*/
/*             for LC4 assembly.  It will be called by main()			*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>

int reverse_assemble (row_of_memory* memory)
{
  /* binary constants should be proceeded by a 0b as in 0b011 for decimal 3 */

	//Data section starts at address 2000, so want to search for opcode 0001 and address < 2000 and assembly = NULL;

	//set current node = head node
	row_of_memory* current = memory;
	short unsigned int opcode = 1;
	short unsigned int subopcode = 0;
	short unsigned int rd = 0;
	short unsigned int rs = 0;
	short unsigned int rt = 0;
	char* assembly_chars = (char*) calloc(16, sizeof(char));
	short unsigned int curr_contents = 0;

	assembly_chars[4] = ' ';
	assembly_chars[5] = 'R';
	assembly_chars[7] = ',';
	assembly_chars[8] = ' ';
	assembly_chars[9] = 'R';
	assembly_chars[11] = ',';
	assembly_chars[12] = ' ';
	assembly_chars[13] = 'R';  // will write over this one in the case of add immediate;
	assembly_chars[15] = '\0';


	//row_of_memory* search_opcode  (row_of_memory* head,
	//			      short unsigned int opcode  )
	// while current node != NULL:
	while (current) {

			current = search_opcode  (memory, opcode);
			if (current == NULL) {
					break;
			}
			// otherwise we have found a node with contents that need to be translated to assembly
			else {

					curr_contents = current->contents;
					//assembly_chars[0];

					// the contents looks like 0001 000 000 000 000
					// we first isolate the subopcode
					subopcode = ((curr_contents >> 3) & 0x7);
					rd = ((curr_contents >> 9) & 0x7);
					rs = ((curr_contents >> 6) & 0x7);
					rt = (curr_contents & 0x7);

					printf("subopcode is: %d\n", subopcode);
					printf("RD is R%d\n", rd);
					printf("RS is R%d\n", rs);
					printf("RT is R%d\n", rt);

					assembly_chars[6] = rd;
					assembly_chars[10] = rs;
					assembly_chars[14] = rt;

					//ADD subopcode = 000
					if(subopcode == 0)	{
							assembly_chars[0] = 'A';
							assembly_chars[1] = 'D';
							assembly_chars[2] = 'D';
							current->assembly = assembly_chars;
					}
					//MUL subopcode = 001
					else if (subopcode == 1) {
							assembly_chars[0] = 'M';
							assembly_chars[1] = 'U';
							assembly_chars[2] = 'L';
							current->assembly = assembly_chars;
					}
					//SUB subopcode = 010
					else if (subopcode == 2) {
							assembly_chars[0] = 'S';
							assembly_chars[1] = 'U';
							assembly_chars[2] = 'B';
							current->assembly = assembly_chars;
					}
					//DIV subopcode = 011
					else if (subopcode == 3) {
							assembly_chars[0] = 'D';
							assembly_chars[1] = 'I';
							assembly_chars[2] = 'V';
							current->assembly = assembly_chars;
					}
					//ADD IMM subopcode = 100
					else if (subopcode >> 2 == 1) {
							assembly_chars[0] = 'A';
							assembly_chars[1] = 'D';
							assembly_chars[2] = 'D';
							assembly_chars[13] = '#';
							current->assembly = assembly_chars;
							//assembly_chars


					}		
					else {printf("The subopcode doesn't match anything!");}
			}
	}

	return 0 ;
}

