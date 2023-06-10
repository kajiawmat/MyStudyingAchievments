#ifndef MYSIMPLECOMPUTER_H
#define MYSIMPLECOMPUTER_H

#define OverFlow 1
#define ZeroDivision 2
#define MemoryOut 3
#define TactIgnore 4
#define ErrorCommand 5

#define READ 0x10
#define WRITE 0x11
#define LOAD 0x20
#define STORE 0x21
#define ADD 0x30
#define SUB 0x31
#define DIVIDE 0x32
#define MUL 0x33
#define JUMP 0x40
#define JNEG 0x41
#define JZ 0x42
#define HALT 0x43
#define NOT 0x51
#define AND 0x52
#define OR 0x53
#define XOR 0x54
#define JNS 0x55
#define JC 0x56
#define JNC 0x57
#define JP 0x58
#define JNP 0x59
#define CHL 0x60
#define SHR 0x61
#define RCL 0x62
#define RCR 0x63
#define NEG 0x64
#define ADDC 0x65
#define SUBC 0x66
#define LOGLC 0x67
#define LOGRC 0x68
#define RCCL 0x69
#define RCCR 0x70
#define MOVA 0x71
#define MOVR 0x72
#define MOVCA 0x73
#define MOVCR 0x74

static int Memory[100];
static int Flags;
static int sc_accumulator;
static int sc_instructionCounter;


int sc_regSet(int flag, int value);
int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit();
int sc_regGet(int flag, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);

#endif
