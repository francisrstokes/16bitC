#include <stdint.h>
#include <stdio.h>
#include "./memory.h"
#include "./cpu.h"

int main() {
  // Create memory and registers
  uint16_t memory[MEM_SIZE];
  Registers registers;

	char* filepath = "test.bin";
	loadProgram(&memory, filepath);
	printf("Done loading program.\n");

  initialiseRegisters(&registers);
	printf("Initialised registers.\n");

  printf("Instruction %d: %d\n", registers.IP, fetchInstruction(memory, &registers));
	return 0;
};

