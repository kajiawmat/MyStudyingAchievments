#pragma once

#include "ILab.h"
#include "BMP_File.h"
#include <vector>
#include <string>

class Lab1: public ILab
{
public:
	void Run() override;
	/*
private:
	void ReadBMPInfo(struct BMP_Info &bmp_info, FILE* f);
	void WriteBMPInfo(struct BMP_Info bmp_info, FILE* f);

	std::vector<Color>	ReadBMPPalitra(struct BMP_Info bmp_info, FILE* f);
	void						WriteBMPPalitra(struct BMP_Info bmp_info, std::vector<Color> palitra, FILE* f);

	void CopyOtherData(struct BMP_Info bmp_info, FILE* f_in, FILE* f_out);

	void PrintBmpInfo(struct BMP_Info bmp_info);
	*/
};

