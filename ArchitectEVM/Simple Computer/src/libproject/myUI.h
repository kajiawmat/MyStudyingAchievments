#ifndef MYUI_H
#define MYUI_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include<malloc.h>
#include "myBigChars.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myReadkey.h"

static const char fl[5]={'O','Z','M','T','E'};
static int Memory_Position;

char* ui_s10_To_S16(int x);
int ui_CreateBigChar(long int Big[], int num);
int ui_input(int operand);
int ui_output(int operand);
int ui_s16_To_S10(char* str, int *value);
int ui_print_number(int address);
int ui_print_memory();
int ui_print_accumulator();
int ui_print_instructionCounter();
int ui_print_operation();
int ui_print_flags();
int ui_set_accumulator();
int ui_terminal_init();
int ui_print_bigNumber();
void ui_SetMemoryPosition(int ind);
int ui_terminal_update();
int ui_Change_Memory_Position(enum keys key, int flag);
int ui_set_memory_value();
int ui_set_instructionCounter(int *value);
int ui_run(int step);
int ui_pause(int time);
int ui_messageOut(char *str);
int ui_clearBuffIn();
int ui_saveMemory();
int ui_loadMemory();
int signalRun(int *value);
int main_setICounter();
int ALU();
int ui_restart();

#endif
