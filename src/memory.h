#ifndef MEMORY_FUNCTIONS
#define MEMORY_FUNCTIONS

#include <stdint.h>

// Definitions
#define MEM_SIZE 0xFFFF
#define STACK_SIZE 0x64
#define STACK_TO_MEM(X) (MEM_SIZE - X)

// Functions
void loadProgram(uint16_t (*memory)[MEM_SIZE], char *path);

#endif
