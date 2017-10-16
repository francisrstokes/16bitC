#ifndef MEMORY_FUNCTIONS
#define MEMORY_FUNCTIONS

#include <stdint.h>

// Definitions
#define MEM_SIZE 0xFFFF

// Variables
extern uint16_t memory[MEM_SIZE];

// Functions
void loadProgram(char *path);

#endif