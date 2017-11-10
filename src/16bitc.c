#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "./memory.h"
// #include "./cpu.h"

#define VERSION "0.1.2"
#define ARGS_MAX 128

static int option(const char *small, const char *large, const char *arg);
static void usage();

static char *cmd[2] = { NULL, NULL };

static int option(const char *small, const char *large, const char *arg)
{
  if (!strcmp(small, arg) || !strcmp(large, arg))
    return 1;
  return 0;
}

static void usage()
{
  printf(
      "\n"
      "  usage: 16bitc [options] <file>\n"
      "\n"
      "  options:\n"
      "\n"
      "    -h, --help            display this help message\n"
      "    -V, --version         display the version number\n"
      "\n");
  exit(1);
}

int main(int argc, char **argv)
{
  if (1 == argc)
    usage();

  int len = 0;
  int interpret = 1;
  char *args[ARGS_MAX] = {0};

  for (int i = 1; i < argc; ++i)
  {
    const char *arg = argv[i];

    if (!interpret) {
      goto arg;
    }

    if (option("-h", "--help", arg)) {
      usage();
    }

    if (option("-V", "--version", arg))
    {
      printf("%s\n", VERSION);
      exit(1);
    }

    if (len == ARGS_MAX)
    {
      fprintf(stderr, "number of arguments exceeded %d\n", len);
      exit(1);
    }

  arg:
    args[len++] = (char *)arg;
    interpret = 0;
  }

  if (!len)
  {
    fprintf(stderr, "\n  <file> required\n");
    usage();
  }

  *(cmd + 2) = args[0];

  // options.file = cmd[0];
  // options.args = cmd;


  // *(cmd + 2) = args[0];

  // Create memory and registers
  // uint16_t memory[MEM_SIZE];
  // uint16_t registers[NUM_REGISTERS] = {0};

  // char *filepath = "fac.bin";
  // loadProgram(&memory, filepath);
  // printf("Done loading program.\n");

  // uint16_t instruction = fetchInstruction(memory, registers);
  // InstructionSplit split = splitInstruction(instruction);
  // printf("opcode: 0x%x\n", split.opcode);
  // printf("dest: 0x%x\n", split.dest);
  // printf("source: 0x%x\n", split.source);
  // printf("high8: 0x%x\n", split.high8);
  // printf("high10: 0x%x\n", split.high10);

  // instruction = fetchInstruction(memory, registers);
  // split = splitInstruction(instruction);
  // printf("opcode: 0x%x\n", split.opcode);
  // printf("dest: 0x%x\n", split.dest);
  // printf("source: 0x%x\n", split.source);
  // printf("high8: 0x%x\n", split.high8);
  // printf("high10: 0x%x\n", split.high10);

  return 0;
};
