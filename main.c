#include <stdint.h>
#include <stdio.h>
#include "./memory.h"
#include "./cpu.h"

int main() {
  // Create memory and registers
  uint16_t memory[MEM_SIZE];
  uint16_t registers[NUM_REGISTERS] = {0};

	char* filepath = "fac.bin";
	loadProgram(&memory, filepath);
	printf("Done loading program.\n");

  uint16_t instruction = fetchInstruction(memory, registers);
  InstructionSplit split = splitInstruction(instruction);
  printf("opcode: 0x%x\n", split.opcode);
  printf("dest: 0x%x\n", split.dest);
  printf("source: 0x%x\n", split.source);
  printf("high8: 0x%x\n", split.high8);
  printf("high10: 0x%x\n", split.high10);

  instruction = fetchInstruction(memory, registers);
  split = splitInstruction(instruction);
  printf("opcode: 0x%x\n", split.opcode);
  printf("dest: 0x%x\n", split.dest);
  printf("source: 0x%x\n", split.source);
  printf("high8: 0x%x\n", split.high8);
  printf("high10: 0x%x\n", split.high10);


	return 0;
};

