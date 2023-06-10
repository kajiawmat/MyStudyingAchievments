#ifndef MYBIGCHARS_H
#define MYBIGCHARS_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "myTerm.h"


static const long int zero[2]={0b10000001100000011000000111111111, 0b11111111100000011000000110000001 };
static const long int one[2]={0b10011000101100001110000011000000, 0b10000000100000001000000010000000 };
static const long int two[2]={0b11111111100000001000000011111111, 0b11111111000000010000000100000001 };
static const long int three[2]={0b11111111100000001000000011111111, 0b11111111100000001000000010000000 };
static const long int four[2]={0b11111111100000011000000110000001, 0b10000000100000001000000010000000 };
static const long int five[2]={0b11111111000000010000000111111111, 0b11111111100000001000000010000000 };
static const long int six[2]={0b11111111000000010000000111111111, 0b11111111100000011000000110000001 };
static const long int seven[2]={0b00110000011000001100000011111111, 0b00000011000001100000110000011000 };
static const long int eight[2]={0b11111111100000011000000111111111, 0b11111111100000011000000110000001 };
static const long int nine[2]={0b11111111100000011000000111111111, 0b11111111100000001000000010000000 };
static const long int ten[2]={0b11111111100000011000000111111111, 0b10000001100000011000000110000001 };
static const long int eleven[2]={0b01111111100000011000000101111111, 0b01111111100000011000000110000001 };
static const long int twelve[2]={0b00000001000000010000000111111111, 0b11111111000000010000000100000001 };
static const long int thirteen[2]={0b10000001100000011000000101111111, 0b01111111100000011000000110000001 };
static const long int fourteen[2]={0b11111111000000010000000111111111, 0b11111111000000010000000100000001 };
static const long int fifteen[2]={0b11111111000000010000000111111111, 0b00000001000000010000000100000001 };
static const long int SymbPlus[2]={0b11111111000110000001100000011000, 0b00011000000110000001100011111111 };
static const long int SymbMinus[2]={0b11111111000000000000000000000000, 0b00000000000000000000000011111111};

static const long int BigChars[18][2]={{zero[0],zero[1]},{one[0],one[1]},{two[0],two[1]},{three[0],three[1]},{four[0],four[1]},{five[0],five[1]},{six[0],six[1]},{seven[0],seven[1]},{eight[0],eight[1]},{nine[0],nine[1]},{ten[0],ten[1]},{eleven[0],eleven[1]},{twelve[0],twelve[1]},{thirteen[0],thirteen[1]},{fourteen[0],fourteen[1]},{fifteen[0],fifteen[1]},{SymbPlus[0],SymbPlus[1]},{SymbMinus[0],SymbMinus[1]}};

int bc_printA(char * str);

int bc_box(int x1, int y1, int x2, int y2);

int bc_printbigchar (long int* nums, int x, int y, enum colors col_bg, enum colors col_fg);

int bc_setbigcharpos(long int* big, int x, int y, int value);

int bc_getbigcharpos(long int* big, int x, int y, int* value);

int bc_bigcharwrite(char* fd, long int* big, int N, int count);

int bc_bigcharread(char* fd, long int* big, int N, int need_count, int* count);


#endif
