#include <stdint.h>
#include "./memory.h"

#ifndef CPU_FUNCTIONS
#define CPU_FUNCTIONS

/*
  Registers
*/
#define NUM_REGISTERS 0x6
#define RA 0x0
#define RB 0x1
#define RC 0x2
#define RD 0x3
#define IP 0x4
#define SP 0x5

/*
  Instructions
*/
#define MVR 0x0
#define MVV 0x1
#define LDR 0x2
#define STA 0x3
#define ATH 0x4
#define CAL 0x5
#define JCP 0x6
#define PSH 0x7
#define POP 0x8
#define JMP 0x9
#define JMR 0xa
#define LDA 0xb
#define STR 0xc
#define NOA 0xd

/*
  MVV
*/
#define MVI 0x0
#define ADI 0x1
#define MUI 0x2
#define AUI 0x3

/*
  ATH
*/
#define ADD 0x0
#define SUB 0x1
#define MUL 0x2
#define DIV 0x3
#define INC 0x4
#define DEC 0x5
#define LSF 0x6
#define RSF 0x7
#define AND 0x8
#define OR  0x9
#define XOR 0xa
#define NOT 0xb
#define DEST_MODE 0x0

/*
  JCP
*/
#define EQ  0x0
#define NEQ 0x1
#define LT  0x2
#define GT  0x3
#define LTE 0x4
#define GTE 0x5
#define ZER 0x6
#define NZE 0x7
#define R1  0x4
#define R2  0x6
#define AR  0x8
#define OP  0xa

/*
  NOA
*/
#define NOP 0x1
#define RET 0x2
#define SYS 0x3
#define HLT 0x4

typedef struct {
  // Default
  uint8_t opcode;
  uint8_t dest;
  uint8_t source;
  uint8_t high8;
  uint16_t high10;
  uint16_t full;

  // ATH
  uint8_t operation;
  uint8_t shiftAmount;
  uint8_t resultReg;
} InstructionSplit; // 0x56 bytes

// Functions
uint16_t fetchInstruction(uint16_t memory[MEM_SIZE], uint16_t registers[NUM_REGISTERS]);
int decodeAndExecute(uint16_t instruction, uint16_t memory[MEM_SIZE], uint16_t registers[NUM_REGISTERS]);
InstructionSplit splitInstruction(uint16_t instruction);

#endif
