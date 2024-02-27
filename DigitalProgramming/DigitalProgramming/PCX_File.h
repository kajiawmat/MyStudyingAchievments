#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "Structs.h"

class PCX_File
{
public:
	PCX_File(std::string filename);

	bool    Init();
	bool    Reset();

	void	PrintInfo();

	unsigned short GetWidth() { return m_info->XMax - m_info->XMin + 1; }
	unsigned short GetHeight() { return m_info->YMax - m_info->YMin + 1; }

	unsigned long GetLineLength() { return m_info->Planes * m_info->BytePerLine; }

	const Color		GetPixelColor(unsigned int i, unsigned int j);
	void			SetPixelColor(unsigned int i, unsigned int j, Color color);

	const std::vector<Color>&	GetPalitra() { return m_palitra; }
	const std::vector<Color>&	GetPixelColors() { return m_pixelColors; }

	static void ConvertWithIncXMax(std::string f1, std::string f2);
private:
	struct Info
	{
		unsigned char ID;
		unsigned char Version;
		unsigned char Coding;
		unsigned char BitPerPixel;
		unsigned short XMin;
		unsigned short YMin;
		unsigned short XMax;
		unsigned short YMax;
		unsigned short HRes;
		unsigned short VRes;
		unsigned char Palette[48];
		unsigned char Reserved;
		unsigned char Planes;
		unsigned short BytePerLine;
		unsigned short PaletteInfo;
		unsigned short HScreenSize;
		unsigned short VScreenSize;
		unsigned char Filler[54];
	};

	Info* m_info;
	std::vector<Color> m_palitra;
	std::vector<Color> m_pixelColors;

	std::string	m_filename;

	bool    ReadFile(FILE* file);
	bool    ReadInfo(FILE* file);
	bool	ReadImageData(FILE* file);

	unsigned long GetPaddind();

	unsigned short      GetPalitraIndOfColor(Color color);
	unsigned long long  GetDiffColor(Color x, Color y);
};

