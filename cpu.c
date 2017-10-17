#include <stdio.h>
#include "./cpu.h"

void initialiseRegisters(Registers *reg) {
  reg->A = 0;
  reg->B = 0;
  reg->C = 0;
  reg->D = 0;
  reg->IP = 0;
  reg->SP = 0;
}

uint16_t fetchInstruction(uint16_t memory[65535], Registers *reg) {
  return *(memory + reg->IP++);
}
