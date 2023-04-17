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
	short unsigned int last5 = 0;
	short unsigned int curr_contents = 0;

	//row_of_memory* search_opcode  (row_of_memory* head,
	//			      short unsigned int opcode  )
	// while current node != NULL:
	while (current) {

			current = search_opcode(memory, opcode);
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
					last5 = (curr_contents & 0x1F);
					printf("last 5 are: %2X\n", last5);

					char rd_char = rd + '0';
					char rs_char = rs + '0';
					char rt_char = rt + '0';

					printf("subopcode is: %d\n", subopcode);
					printf("RD is R%d\n", rd);
					printf("RS is R%d\n", rs);
					printf("RT is R%d\n", rt);	

					printf("rd_char is: %c\n", rd_char);
					printf("rs_char is: %c\n", rs_char);
					printf("rt_char is: %c\n", rt_char);

					//ADD subopcode = 000
					if(subopcode == 0)	{
							printf("this is an ADD\n");
							char* assembly_chars = (char*) calloc(30, sizeof(char));
	
							assembly_chars[0] = 'A';
							assembly_chars[1] = 'D';
							assembly_chars[2] = 'D';
							assembly_chars[3] = ' ';
							assembly_chars[4] = 'R';
							assembly_chars[5] = rd_char;
							assembly_chars[6] = ',';
							assembly_chars[7] = ' ';
							assembly_chars[8] = 'R';
							assembly_chars[9] = rs_char;
							assembly_chars[10] = ',';
							assembly_chars[11] = ' ';
							assembly_chars[12] = 'R';  // will write over this one in the case of add immediate;
							assembly_chars[13] = rt_char;
							assembly_chars[14] = '\0';

							current->assembly = assembly_chars;
					}
					//MUL subopcode = 001
					else if (subopcode == 1) {
							printf("this is an MUL\n");
								char* assembly_chars = (char*) calloc(30, sizeof(char));
	
							assembly_chars[0] = 'M';
							assembly_chars[1] = 'U';
							assembly_chars[2] = 'L';
							assembly_chars[3] = ' ';
							assembly_chars[4] = 'R';
							assembly_chars[5] = rd_char;
							assembly_chars[6] = ',';
							assembly_chars[7] = ' ';
							assembly_chars[8] = 'R';
							assembly_chars[9] = rs_char;
							assembly_chars[10] = ',';
							assembly_chars[11] = ' ';
							assembly_chars[12] = 'R';  // will write over this one in the case of add immediate;
							assembly_chars[13] = rt_char;
							assembly_chars[14] = '\0';

							current->assembly = assembly_chars;
					}
					//SUB subopcode = 010
					else if (subopcode == 2) {
							printf("this is an SUB\n");
							char* assembly_chars = (char*) calloc(30, sizeof(char));
	
							assembly_chars[0] = 'S';
							assembly_chars[1] = 'U';
							assembly_chars[2] = 'B';
							assembly_chars[3] = ' ';
							assembly_chars[4] = 'R';
							assembly_chars[5] = rd_char;
							assembly_chars[6] = ',';
							assembly_chars[7] = ' ';
							assembly_chars[8] = 'R';
							assembly_chars[9] = rs_char;
							assembly_chars[10] = ',';
							assembly_chars[11] = ' ';
							assembly_chars[12] = 'R';  // will write over this one in the case of add immediate;
							assembly_chars[13] = rt_char;
							assembly_chars[14] = '\0';

							current->assembly = assembly_chars;
					}
					//DIV subopcode = 011
					else if (subopcode == 3) {
							printf("this is an DIV\n");
							char* assembly_chars = (char*) calloc(30, sizeof(char));
	
							assembly_chars[0] = 'D';
							assembly_chars[1] = 'I';
							assembly_chars[2] = 'V';
							assembly_chars[3] = ' ';
							assembly_chars[4] = 'R';
							assembly_chars[5] = rd_char;
							assembly_chars[6] = ',';
							assembly_chars[7] = ' ';
							assembly_chars[8] = 'R';
							assembly_chars[9] = rs_char;
							assembly_chars[10] = ',';
							assembly_chars[11] = ' ';
							assembly_chars[12] = 'R';  // will write over this one in the case of add immediate;
							assembly_chars[13] = rt_char;
							assembly_chars[14] = '\0';
							current->assembly = assembly_chars;
					}
					//ADD IMM subopcode = 100
					else if (subopcode >> 2 == 1) {
							printf("this is an ADD IMM\n");
							char* assembly_chars = (char*) calloc(30, sizeof(char));
	
							assembly_chars[0] = 'A';
							assembly_chars[1] = 'D';
							assembly_chars[2] = 'D';
							assembly_chars[3] = ' ';
							assembly_chars[4] = 'R';
							assembly_chars[5] = rd_char;
							assembly_chars[6] = ',';
							assembly_chars[7] = ' ';
							assembly_chars[8] = 'R';
							assembly_chars[9] = rs_char;
							assembly_chars[10] = ',';
							assembly_chars[11] = ' ';
							assembly_chars[12] = '#'; 

							if (last5 < 10) {
									char last5_char = last5 + '0';
									printf("last 5 is %d\n", last5);
									printf("last5_char is %c\n", last5_char);

									assembly_chars[13] = last5_char;
									assembly_chars[14] = '\0';
							}
							// if # greater than 10, we need to use to characters, so need to break it up.  Note max number is 
							else {
									int last5_first = last5/10;
									int last5_last = last5 - (last5_first * 10);
									char l5_first_char = last5_first + '0';
									char l5_last_char = last5_last + '0';

									printf("last 5 is %d\n", last5);
									printf("last5_first is %d\n", last5_first);
									printf("last5_last is %d\n", last5_last);
									printf("last5_first char is %c\n", l5_first_char);
									printf("last5_last char is %c\n", l5_last_char);

									assembly_chars[13] = l5_first_char;
									assembly_chars[14] = l5_last_char;
									assembly_chars[15] = '\0';
							}

							current->assembly = assembly_chars;
							//assembly_chars


					}		
					else {printf("The subopcode doesn't match anything!");}
			}
	}

	return 0 ;
}

