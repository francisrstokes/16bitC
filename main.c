#include <stdint.h>
#include <stdio.h>
#include "./memory.h"

int main() {
	char* filepath = "test.bin";
	loadProgram(filepath);
	printf("Done loading program.\n");

	for (int i = 0; i < 10; i++) {
		printf("%x\n", memory[i]);
	}
	return 0;
};

