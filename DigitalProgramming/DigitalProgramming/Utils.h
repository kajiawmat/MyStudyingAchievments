#pragma once

const unsigned int BitPerByte = 8;

unsigned char GetBits(unsigned char byte, unsigned int ind, unsigned int count);
unsigned char SetBitsInto(unsigned char byte, unsigned int ind, unsigned int count, unsigned char value, unsigned char& buffer);
unsigned char SetBits(unsigned char byte, unsigned int ind, unsigned int count, unsigned char value);