#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "./cpu.h"

/*
  Private functions
*/
static void pushStack(uint16_t value, uint16_t memory[MEM_SIZE], uint16_t registers[NUM_REGISTERS]) {
  memory[STACK_TO_MEM(registers[SP])] = value;
  if (++registers[SP] >= STACK_SIZE) {
    printf("VM stack overflow.\n");
    exit(1);
  }
}

static uint16_t popStack(uint16_t memory[MEM_SIZE], uint16_t registers[NUM_REGISTERS]) {
  if (registers[SP] < 0) {
    printf("VM stack underflow.\n");
    exit(1);
  }
  return memory[STACK_TO_MEM(registers[SP]--)];
}

static void executeMVV(InstructionSplit ins, uint16_t registers[NUM_REGISTERS]) {
  switch (ins.high10 & 0x3) {
    case MVI:
      registers[ins.dest] = (uint16_t)ins.high8;
      break;
    case ADI:
      registers[ins.dest] = (uint16_t)((registers[ins.dest] << 16) >> 16) + (uint16_t)((ins.high8 << 24) >> 24);
      break;
    case MUI:
      registers[ins.dest] = (uint16_t)(ins.high8 << 8);
      break;
    case AUI:
      registers[ins.dest] += (uint16_t)(ins.high8 << 8);
      break;
  }
}

static void executeATH(InstructionSplit ins, uint16_t registers[NUM_REGISTERS]) {
  switch (ins.operation) {
    case ADD:
      registers[ins.resultReg] = registers[ins.dest] + registers[ins.source];
      break;
    case SUB:
      registers[ins.resultReg] = registers[ins.dest] - registers[ins.source];
      break;
    case MUL:
      registers[ins.resultReg] = registers[ins.dest] * registers[ins.source];
      break;
    case DIV:
      registers[ins.resultReg] = registers[ins.dest] / registers[ins.source];
      break;
    case INC:
      registers[ins.dest]++;
      break;
    case DEC:
      registers[ins.dest]--;
      break;
    case LSF:
      registers[ins.resultReg] = (uint16_t)(registers[ins.dest] << ins.shiftAmount);
      break;
    case RSF:
      registers[ins.resultReg] = (uint16_t)(registers[ins.dest] >> ins.shiftAmount);
      break;
    case AND:
      registers[ins.resultReg] = registers[ins.dest] & registers[ins.source];
      break;
    case OR:
      registers[ins.resultReg] = registers[ins.dest] | registers[ins.source];
      break;
    case XOR:
      registers[ins.resultReg] = registers[ins.dest] ^ registers[ins.source];
      break;
    case NOT:
      registers[ins.resultReg] = ~registers[ins.dest];
      break;
  }
}

static void executeJCP(InstructionSplit ins, uint16_t registers[NUM_REGISTERS]) {
  const uint16_t jumpAddress = registers[ins.high8 & 0x3];

  switch (ins.high8 >> 2) {
    case EQ:
      if (registers[ins.dest] == registers[ins.source]) {
        registers[IP] = jumpAddress;
      }
      break;
    case NEQ:
      if (registers[ins.dest] != registers[ins.source]) {
        registers[IP] = jumpAddress;
      }
      break;
    case LT:
      if (registers[ins.dest] < registers[ins.source]) {
        registers[IP] = jumpAddress;
      }
      break;
    case GT:
      if (registers[ins.dest] > registers[ins.source]) {
        registers[IP] = jumpAddress;
      }
      break;
    case LTE:
      if (registers[ins.dest] <= registers[ins.source]) {
        registers[IP] = jumpAddress;
      }
      break;
    case GTE:
      if (registers[ins.dest] >= registers[ins.source]) {
        registers[IP] = jumpAddress;
      }
      break;
    case ZER:
      if (registers[ins.dest] == 0) {
        registers[IP] = jumpAddress;
      }
      break;
    case NZE:
      if (registers[ins.dest] != 0) {
        registers[IP] = jumpAddress;
      }
      break;
  }
}

static void executeJMP(InstructionSplit ins, uint16_t registers[NUM_REGISTERS]) {
  const uint16_t jumpOffset = ins.full >> 4;
  registers[IP] += -(jumpOffset & 0x800) | (jumpOffset & ~0x800);
}

static void executeSTR(InstructionSplit ins, uint16_t memory[MEM_SIZE], uint16_t registers[NUM_REGISTERS]) {
  const uint16_t address = ((uint16_t)(registers[ins.dest] << 16) + (uint16_t)((uint16_t)(ins.high8 << 24) >> 8)) >> 16;
  memory[address] = registers[ins.source];
}
/*
  Public functions
*/
uint16_t fetchInstruction(uint16_t memory[MEM_SIZE], uint16_t registers[NUM_REGISTERS]) {
  return *(memory + registers[IP]++);
}

InstructionSplit splitInstruction(uint16_t instruction) {
  InstructionSplit out;
  out.full = instruction;
  out.opcode = out.full & 0xF;
  out.dest = (out.full & 0x30) >> 4;
  out.source = (out.full & 0xC0) >> 6;
  out.high8 = (out.full & 0xFF00) >> 8;
  out.high10 = (out.full & 0xFFC0) >> 10;

  out.operation = (out.high8 & 0xF);
  out.shiftAmount = (out.high8 & 0xE0) >> 5;
  out.resultReg = (((out.high8 & 0x10) >> 4) == DEST_MODE)
    ? out.dest
    : out.source;
  return out;
}

int decodeAndExecute(uint16_t instruction, uint16_t memory[MEM_SIZE], uint16_t registers[NUM_REGISTERS]) {
  InstructionSplit ins = splitInstruction(instruction);

  switch (ins.opcode) {
    case MVR:
      registers[ins.dest] = (uint16_t)((uint16_t)(registers[ins.source] << 16) >> 16) +
        (uint16_t)((uint16_t)(ins.high8 << 24) >> 24);
      return 0;

    case MVV:
      executeMVV(ins, registers);
      return 0;

    case LDR:
      registers[ins.dest] = memory[
        (uint16_t)(((uint16_t)(registers[ins.dest] << 16) +
        (uint16_t)((uint16_t)(ins.high8 << 24) >> 8)) >> 16)
      ];
      return 0;

    case STA:
      memory[ins.high10] = registers[ins.dest];
      return 0;

    case ATH:
      executeATH(ins, registers);
      break;

    case CAL:
      pushStack(registers[IP], memory, registers);
      registers[IP] = registers[ins.dest];
      return 0;

    case JCP:
      executeJCP(ins, registers);
      return 0;

    case PSH:
      pushStack(registers[ins.source], memory, registers);
      return 0;

    case POP:
      registers[ins.dest] = popStack(memory, registers);
      return 0;

    case JMP:
      executeJMP(ins, registers);
      return 0;

    case JMR:
      registers[IP] = registers[ins.dest];
      return 0;

    case LDA:
      registers[ins.dest] = memory[ins.high10];
      return 0;

    case STR:
      executeSTR(ins, memory, registers);
      return 0;

    case NOA:
      switch ((ins.full & 0xF0) >> 4) {
        case NOP:
          return 0;

        case RET:
          registers[IP] = popStack(memory, registers);
          return 0;

        case SYS:
          // Not implemented
          return 0;

        case HLT:
          return 1;
      }
  }

  // Exit with a a halt since we should only arrive here if an invalid instruction is used
  return 1;
}
