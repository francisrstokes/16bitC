#ifndef MEMORY_FUNCTIONS
#define MEMORY_FUNCTIONS

#include <stdint.h>

// Definitions
#define MEM_SIZE 0xFFFF

// Functions
void loadProgram(uint16_t (*memory)[MEM_SIZE], char *path);

#endif
