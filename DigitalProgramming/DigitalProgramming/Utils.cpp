#include "Utils.h"

unsigned char GetBits(unsigned char byte, unsigned int ind, unsigned int count)
{
	byte &= static_cast<unsigned char>((1 << (BitPerByte - ind)) - 1);
	byte >>= (BitPerByte - (ind + count));

	return byte;
}
//------------------------------------------------------------------------------
unsigned char SetBitsInto(unsigned char byte, unsigned int ind, unsigned int count, unsigned char value, unsigned char& buffer)
{
	unsigned char res = 0;
	value = GetBits(value, BitPerByte - count, count);
	buffer = GetBits(byte, BitPerByte - count, count);

	res += GetBits(byte, 0, ind) << (BitPerByte - ind);
	res += value << (BitPerByte - (ind + count));
	res += GetBits(byte, ind, BitPerByte - (ind + count));

	return res;
}
//------------------------------------------------------------------------------
unsigned char SetBits(unsigned char byte, unsigned int ind, unsigned int count, unsigned char value)
{
	unsigned char res = 0;
	value = GetBits(value, BitPerByte - count, count);

	res += GetBits(byte, 0, ind) << (BitPerByte - ind);
	res += value << (BitPerByte - (ind + count));
	res += GetBits(byte, ind + count, BitPerByte - (ind + count));

	return res;
}