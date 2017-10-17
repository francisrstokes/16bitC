#include <stdint.h>
#include "./memory.h"

#ifndef CPU_FUNCTIONS
#define CPU_FUNCTIONS

// Structures
typedef struct {
  uint16_t A;
  uint16_t B;
  uint16_t C;
  uint16_t D;
  uint16_t SP;
  uint16_t IP;
} Registers;

// Functions
void initialiseRegisters(Registers *reg);
uint16_t fetchInstruction(uint16_t memory[65535], Registers *reg);
int decodeAndExecute(uint16_t memory[65535], Registers *reg);

#endif
