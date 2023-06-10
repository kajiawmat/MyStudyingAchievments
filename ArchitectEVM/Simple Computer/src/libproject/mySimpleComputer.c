#include<stdlib.h>
#include<stdio.h>
#include"mySimpleComputer.h"


int sc_regSet(int flag, int value) {
    if (flag > 5 || flag < 1) return -1;
    if (value > 2 || value < 0) return -2;
    if (value) Flags = Flags | (1 << (flag - 1));
    else Flags = Flags & (~(1 << (flag - 1)));
    return 0;
}

int sc_memoryInit() {
    for (int i = 0; i < 100; i++) Memory[i] = 0;
    return 0;
}

int sc_memorySet(int address, int value) {
    if (address < 100 && address >= 0) {
        Memory[address] = value;
        return 0;
    } else {
        sc_regSet(MemoryOut, 1);
        return -1;
    }
}

int sc_memoryGet(int address, int * value) {
    if (address < 100 && address >= 0) {
        * value = Memory[address];
        return 0;
    } else {
        return -1;
    }
}

int sc_memorySave(char * filename) {
    FILE * fp = fopen(filename, "w+");
    for (int i = 0; i < 100; i++) {
        fwrite((char * ) & Memory[i], sizeof(int), 1, fp);
    }
    return 0;
}

int sc_memoryLoad(char * filename) {
    FILE * fp = fopen(filename, "r");
    if (fp == NULL) return -1;
    for (int i = 0; i < 100; i++) {
        fread((char * ) & Memory[i], sizeof(int), 1, fp);
    }
    return 0;
}

int sc_regInit() {
    Flags = 0;
    return 0;
}

int sc_regGet(int flag, int * value) {
    if (flag > 5 || flag < 1) return -1;
    * value = (Flags >> (flag - 1)) & 0x1;
    return 0;
}

int sc_commandEncode(int command, int operand, int * value) {
    if (command > 127 || command < 0) {
        sc_regSet(ErrorCommand, 1);
        return -1;
    }
    if (operand > 127 || operand < 0) return -2;
    * value = 0;
    * value = * value | (command << (8 - 1));
    * value = * value | operand;
    return 0;
}

int sc_commandDecode(int value, int * command, int * operand) {
    if (value >> (15 - 1) > 1) return -1;
    if (value >> (15 - 1) & 0x1) return 1;
    * command = value >> (8 - 1);
    * operand = value & 127;
    return 0;
}
