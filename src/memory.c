#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "./memory.h"

void loadProgram(uint16_t (*memory)[MEM_SIZE], char *path) {
  FILE *fp;
  size_t size;

  fp = fopen(path, "rb");

  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  if (size > MEM_SIZE) {
    printf("Error: File %s is larger than maximum memory size\n", path);
    exit(1);
  }

  if (fp == NULL) {
    printf("Error: There was an Error reading the file %s \n", path);
    exit(1);
  }

  fread(memory, size, 1, fp);
}
