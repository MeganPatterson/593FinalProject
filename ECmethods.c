
#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>

/////////////////////////////////create a file///////////////////


void write_asm_file() {
  FILE *fptr;
  fptr = fopen("All_instructions.asm", "w");   // CREATES A FILE TO WRITE TODO

  if (fptr == NULL) {
    printf("Failed to create file\n");
    return;
  }

  //fprintf(ADD IN WHAT TO WRITE);  // WRITES INFORMAITON TO THE FILE
  fclose(fptr);
}



///////////////////////////////////////////ATTEMPT 2//////////////////////////////

instruction_FIND* lookup_instruction(unsigned short opcode) {
    int num_instructions = sizeof(lc4_I) / sizeof(instruction_FIND);
    for (int i = 0; i < num_instructions; i++) {
        if (opcode == lc4_I[i].opcode) {
            return &lc4_I[i];
        }
    }
    return NULL; // If the instruction is not found
}


typedef struct {
    char mnemonic[10];
    unsigned short opcode;
    char format;
    char operand_types[5];
} instruction_FIND;

// Define the lookup table


// Column 1: Mnemonic
//Conlumn 2: Opcode: the binary representation of the instruction's operation code.
//Column 3: Format: the format of the instruction (R, I, J, O).
//Column 4: Operand types: R (register), S (signed immediate), B (base register), or D (destination register).


instruction_entry lc4_I[] = {
    
    // Immediate 
    {"BR", 0x0000, 'I', "S"},
	// jump
    {"JMP", 0x1100, 'J', "R"},
    {"JSR", 0x0100, 'J', "S"},

// register 
    {"LD", 0x0010, 'I', "S"},
    {"LDI", 0x1010, 'I', "S"},
    {"LDR", 0x0110, 'R', "DRBS"},
    {"LEA", 0x1110, 'I', "S"},
    

		{"CMP", 0x0010, 'R', "SR"},
    {"CMPU", 0x0110, 'R', "SR"},
    {"CMPI", 0x0011, 'I', "SR"},
    {"CMPIU", 0x0111, 'I', "SR"},		



// other 
    {"RET", 0x1101, 'O', ""},
    {"RTI", 0x1000, 'O', ""},


    {"ST", 0x0011, 'I', "S"},
    {"STI", 0x1011, 'I', "S"},
    {"STR", 0x0111, 'R', "SRDB"},
    {"TRAP", 0x1111, 'O', ""},

		{"AND", 0x0101, 'R', "DRSR"},
		{"NOT", 0x1001, 'R', "DR"},
    {"OR", 0x1101, 'R', "DRSR"},
    {"XOR", 0x1001, 'R', "DRSR"},
    {"ORI", 0x1101, 'I', "DASA"},
    {"XORI", 0x1001, 'I', "DASA"},



		{"ANDI", 0x0101, 'I', "DASA"},
		{"ADD", 0x0001, 'R', "DRSR"},
    {"MUL", 0x1001, 'R', "DRSR"},
    {"SUB", 0x0001, 'R', "DRSR"},
    {"DIV", 0x1001, 'R', "DRSR"},
};
//////////////////////////////////////////////////////////////////////////////////////////
