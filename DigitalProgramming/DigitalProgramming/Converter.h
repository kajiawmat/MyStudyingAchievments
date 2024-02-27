#pragma once
#include "BMP_File.h"
#include "PCX_File.h"
#include "string"

class Converter
{
public:
	void ConvertFromPCXToBMP(std::string filename1, std::string filename2, unsigned short bitPerPixel);
	void ConvertFromBMPToBMP(std::string filename1, std::string filename2, unsigned short bitPerPixel);
};

