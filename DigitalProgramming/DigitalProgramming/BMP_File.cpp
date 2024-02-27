#include "BMP_File.h"
#include "stdafx.h"
#include "Utils.h"
#include "ImageMethods.h"

using namespace std;

BMP_File::BMP_File(std::string filename):
	m_info(nullptr)
{
	m_filename = filename;
}
//------------------------------------------------------------------------------
BMP_File::BMP_File(std::vector<std::vector<unsigned char>> pixels)
{
	m_filename = "";
	m_info = new Info();

	m_info->id = 19778;
	m_info->planes = 1;
	m_info->h_size = 40;
	m_info->bitperpixel = 24;
	
	m_pixels = move(pixels);
	
	UpdateImageProperties();
}
//------------------------------------------------------------------------------
bool BMP_File::Init()
{
	auto file = new FILE();

	try
	{
		fopen_s(&file, m_filename.c_str(), "rb");
	}
	catch (std::exception ex)
	{
		return false;
	}

	auto result = ReadFile(file);
	fclose(file);

	return result;
}
//------------------------------------------------------------------------------
bool BMP_File::Reset()
{
	delete m_info;
	m_palitra.clear();
	m_pixels.clear();
	return Init();
}
//------------------------------------------------------------------------------
void BMP_File::Write(std::string filename)
{
	if (m_info == nullptr)
		return;

	FILE* file = new FILE();

	try
	{
		fopen_s(&file, filename.c_str(), "wb");
	}
	catch (std::exception ex)
	{
		return;
	}

	if (file == nullptr)
		return;

	fwrite(m_info, sizeof(*m_info), 1, file);

	unsigned char byte = 0;
	if (m_info->bitperpixel <= 8)
	{
		for (size_t i = 0; i < m_palitra.size(); i++)
		{
			fwrite(m_palitra[i].values, 1, 3, file);
			fwrite(&byte, 1, 1, file);
		}
	}

	const auto padding = GetPadding();
	for (size_t i = 0; i < m_pixels.size(); i++)
	{
		const auto& vec_row = m_pixels[i];
		const auto Length = GetRowLength();

		for (size_t j = 0; j < Length; j++)
			fwrite(&vec_row[j], 1, 1, file);

		if (padding != 0)
		{
			auto empty_row = new unsigned char[padding];
			for (size_t j = 0; j < padding; j++)
				empty_row[j] = 0;
			fwrite(empty_row, 1, padding, file);

			delete[] empty_row;
		}
	}

	fclose(file);
}
//------------------------------------------------------------------------------
void BMP_File::PrintInfo()
{
	cout << "Id: " << m_info->id << endl;
	cout << "F_size: " << m_info->f_size << endl;
	cout << "Rez1: " << m_info->rez1 << endl;
	cout << "Rez2: " << m_info->rez2 << endl;
	cout << "Offset: " << m_info->bm_offset << endl;
	cout << "H_size: " << m_info->h_size << endl;
	cout << "Width: " << m_info->width << endl;
	cout << "Height: " << m_info->height << endl;
	cout << "Planes: " << m_info->planes << endl;
	cout << "BitPerPixel: " << m_info->bitperpixel << endl;
	cout << "Compression: " << m_info->compression << endl;
	cout << "SizeImage: " << m_info->sizeimage << endl;
	cout << "HRes: " << m_info->hres << endl;
	cout << "VRes: " << m_info->vres << endl;
	cout << "ClrUsed: " << m_info->clrused << endl;
	cout << "ClrImp: " << m_info->clrimp << endl;

	cout << "---------------------------------" << endl;
}
//------------------------------------------------------------------------------
void BMP_File::PrintPalitra()
{
	if (m_palitra.empty())
		return;

	for (int i = 0; i < m_palitra.size(); i++) 
	{
		auto& temp = m_palitra[i];
		for (int j = 0; j < 3; j++)
			cout << std::bitset<8>(temp.values[i]);
		cout << std::endl;
	}

	cout << "---------------------------------" << endl;
}
//------------------------------------------------------------------------------
void BMP_File::PrintPixels()
{
	if (m_pixels.empty())
		return;

	for (auto& row : m_pixels)
	{
		for (int i = 0; i < row.size(); i++)
			cout << std::bitset<8>(row[i]) << " ";
		cout << endl;
	}

	cout << "---------------------------------" << endl;
}
//------------------------------------------------------------------------------
void BMP_File::SetPalitraColor(int ind, Color color)
{
	if (ind > m_palitra.size())
		return;

	m_palitra[ind] = color;
}
//------------------------------------------------------------------------------
const Color BMP_File::GetPalitraColor(int ind)
{
	if (ind > m_palitra.size())
		return Color();

	return m_palitra[ind];
}
//------------------------------------------------------------------------------
void BMP_File::SetPixelColor(int x, int y, Color color)
{
	if (x >= m_info->width || y >= m_info->height)
		return;

	color = ConvertBGRToRGB(color);

	bool usePalitra = m_info->bitperpixel <= 8 && m_palitra.size() != 0;

	if (usePalitra)
	{
		unsigned long long bitInd = x * m_info->bitperpixel;
		unsigned long long byteInd = bitInd / 8;
		unsigned short bitIndMod = bitInd % 8;

		m_pixels[y][byteInd] = SetBits(m_pixels[y][byteInd], bitIndMod, m_info->bitperpixel, GetPalitraIndOfColor(color));
	}
	else
	{
		auto colorBytes = ConvertColorToBytes(color);
		unsigned long long bitInd = x * m_info->bitperpixel;
		unsigned long long byteInd = bitInd / 8;

		for (int i = 0; i < colorBytes.size(); i++)
			m_pixels[y][byteInd + i] = colorBytes[i];
	}
}
//------------------------------------------------------------------------------
const Color BMP_File::GetPixelColor(int x, int y)
{
	if (x >= m_info->width || y >= m_info->height)
		return Color();

	bool usePalitra = m_info->bitperpixel <= 8 && m_palitra.size() != 0;

	if (usePalitra)
	{
		unsigned long long bitInd = x * m_info->bitperpixel;
		unsigned long long byteInd = bitInd / 8;
		unsigned short bitIndMod = bitInd % 8;

		return ConvertBGRToRGB(m_palitra[GetBits(m_pixels[y][byteInd], bitIndMod, m_info->bitperpixel)]);
	}
	
	unsigned long long bitInd = x * m_info->bitperpixel;
	unsigned long long byteInd = bitInd / 8;
	int bytesPerPixel = m_info->bitperpixel / 8;
	auto bytes = vector<unsigned char>(bytesPerPixel, 0);

	for (int i = 0; i < bytesPerPixel; i++)
		bytes[i] = m_pixels[y][byteInd + i];

	auto color = ConvertBytesToColor(bytes);
	
	return ConvertBGRToRGB(color);
}
//------------------------------------------------------------------------------
void BMP_File::InsertPixelRowInto(int pixelInd)
{
	if (pixelInd > m_info->height)
		return;

	m_pixels.insert(m_pixels.begin() + pixelInd, vector<unsigned char>(m_pixels[0].size()));
	UpdateImageProperties();
}
//------------------------------------------------------------------------------
void BMP_File::InsertPixelColumnInto(int pixelInd)
{
	if (pixelInd > m_info->width)
		return;

	bool usePalitra = m_info->bitperpixel <= 8 && m_palitra.size() != 0;
	int new_byte = (((long long)m_info->width + 1) * m_info->bitperpixel) / 8 - ((long long)m_info->width * m_info->bitperpixel) / 8;

	for (int i = 0; i < m_pixels.size(); i++)
	{
		if (usePalitra)
		{
			for (int j = 0; j < new_byte; j++)
				m_pixels[i].push_back(0);

			unsigned char pixel = 0;

			for (unsigned long long j = pixelInd; j < m_info->width; j++)
			{
				unsigned long long bitInd = j * m_info->bitperpixel;
				unsigned long long byteInd = bitInd / 8;
				unsigned short bitIndMod = bitInd % 8;
				
				m_pixels[i][byteInd] = SetBitsInto(m_pixels[i][byteInd], bitIndMod, m_info->bitperpixel, pixel, pixel);
			}
		}
		else
		{
			unsigned long long bitInd = pixelInd * m_info->bitperpixel;
			unsigned long long byteInd = bitInd / 8;

			for (int j = 0; j < new_byte; j++)
				m_pixels[i].insert(m_pixels[i].begin() + byteInd, 0);
		}
	}
	UpdateImageProperties();
}
//------------------------------------------------------------------------------
void BMP_File::SetBitPerPixel(unsigned short bitPerPixel, bool useDithering)
{
	if (m_info->bitperpixel == bitPerPixel)
		return;

	const bool bitPerPixelDecreased = m_info->bitperpixel > bitPerPixel;

	vector<Color> pixelColors;
	for (size_t i = 0; i < GetHeight(); i++)
		for (size_t j = 0; j < GetWidth(); j++)
			pixelColors.emplace_back(ConvertBGRToRGB(GetPixelColor(j, i)));

	m_palitra.clear();
	
	if (bitPerPixel <= 8)
		m_palitra = move(MedianCutPalette(pixelColors, 1 << bitPerPixel));

	m_info->bitperpixel = bitPerPixel;
	vector< vector<unsigned char> > pixels(GetHeight());

	for (size_t i = 0; i < GetHeight(); i++)
		pixels[i] = vector<unsigned char>(GetWidth() * GetBitPerPixel() / BitPerByte);

	for (size_t i = 0; i < m_pixels.size(); i++)
		m_pixels[i].clear();

	m_pixels.clear();
	m_pixels = move(pixels);

	if(useDithering && bitPerPixelDecreased) // אכדמנטעל װכמיהא-״עויםבונדא
		SetAllPixelsColorWithErrors(pixelColors);
	else
		SetAllPixelsColor(pixelColors);

	pixelColors.clear();

	m_info->clrused = m_palitra.size();
	UpdateImageProperties();
}
//------------------------------------------------------------------------------
void BMP_File::SetPixels(std::vector< std::vector<unsigned char> > pixels)
{
	m_pixels = std::move(pixels);
	UpdateImageProperties();
}
//------------------------------------------------------------------------------
bool BMP_File::ReadFile(FILE* file)
{
	return ReadInfo(file) &&
		ReadPalitra(file) &&
		ReadPixels(file);
}
//------------------------------------------------------------------------------
bool BMP_File::ReadInfo(FILE* file)
{
	m_info = new Info();
	fseek(file, 0, SEEK_SET);
	fread(m_info, sizeof(*m_info), 1, file);
	if (ferror(file) != 0)
	{
		delete m_info;
		return false;
	}

	return true;
}
//------------------------------------------------------------------------------
bool BMP_File::ReadPalitra(FILE* file)
{
	m_palitra.clear();
	fseek(file, sizeof(*m_info), SEEK_SET);
	unsigned char byte;

	for (size_t i = 0; i < GetColorTableSize(); i++)
	{
		Color temp = Color();
		fread(temp.values, 1, 3, file);
		if (ferror(file) != 0)
		{
			m_palitra.clear();
			return false;
		}
		fread(&byte, 1, 1, file);

		m_palitra.push_back(temp);
	}

	return true;
}
//------------------------------------------------------------------------------
bool BMP_File::ReadPixels(FILE* file)
{
	m_pixels.clear();
	fseek(file, m_info->bm_offset, SEEK_SET);

	const auto padding = GetPadding();
	
	for (size_t i = 0; i < m_info->height; i++)
	{
		const auto Length = GetRowLength();
		auto row = new unsigned char[Length];
		for (size_t j = 0; j < Length; j++)
		{
			fread(&row[j], 1, 1, file);
			if (ferror(file) != 0)
			{
				m_pixels.clear();
				return false;
			}
		}
		fseek(file, padding, SEEK_CUR);

		m_pixels.push_back(std::vector<unsigned char>(row, row + Length));
		delete row;
	}

	return true;
}
//------------------------------------------------------------------------------
unsigned long BMP_File::GetRowLength()
{
	if (m_info == nullptr)
		return 0;

	return m_info->width * m_info->bitperpixel / 8;
}
//------------------------------------------------------------------------------
unsigned long BMP_File::GetPadding()
{
	if (m_info == nullptr)
		return 0;

	return (m_info->sizeimage / m_info->height * 8 - m_info->width * m_info->bitperpixel) / 8;
}
//------------------------------------------------------------------------------
unsigned long BMP_File::GetColorTableMaxSize()
{
	if (m_info == nullptr)
		return 0;

	if (m_info->bitperpixel > 8)
		return 0;

	return 1 << m_info->bitperpixel;
}
//------------------------------------------------------------------------------
void BMP_File::UpdateImageProperties()
{
	m_info->height = m_pixels.size();
	m_info->width = !m_pixels.empty() ? 
		m_pixels[0].size() * 8 / m_info->bitperpixel : 0;

	auto width = !m_pixels.empty() ? m_pixels[0].size() : 0;
	if (width % 4 != 0)
		width += 4 - width % 4;
	m_info->bm_offset = m_palitra.size() * 4 + sizeof(*m_info);
	m_info->sizeimage = width * m_info->height;
	m_info->f_size = m_info->bm_offset + m_info->sizeimage;
}
//------------------------------------------------------------------------------
unsigned short BMP_File::GetPalitraIndOfColor(Color color)
{
	unsigned short min_ind = 0;
	unsigned long long min_diff = GetDiffColor(m_palitra[0], color);
	for (unsigned long long i = 0; i < m_palitra.size(); i++)
	{
		unsigned long long diff = GetDiffColor(m_palitra[i], color);
		if (diff < min_diff)
		{
			min_ind = i;
			min_diff = diff;
		}
	}

	return min_ind;
}
//------------------------------------------------------------------------------
unsigned long long BMP_File::GetDiffColor(Color x, Color y)
{
	unsigned long long diff = 0;
	diff += 0.11 * (pow(abs(x.values[0] - y.values[0]), 2));
	diff += 0.59 * (pow(abs(x.values[1] - y.values[1]), 2));
	diff += 0.3 * (pow(abs(x.values[2] - y.values[2]), 2));

	return diff;
}
//------------------------------------------------------------------------------
vector<unsigned char> BMP_File::ConvertColorToBytes(Color color)
{
	int bytePerPixel = m_info->bitperpixel / 8;

	if (m_info->bitperpixel % 8 != 0)
		bytePerPixel++;

	auto bytes = vector<unsigned char>(bytePerPixel, 0);

	auto bitsPerGrad = vector<unsigned char>(3, m_info->bitperpixel / 3);

	int gradMod = m_info->bitperpixel % 3;

	if (gradMod-- > 0)
		bitsPerGrad[1]++;

	if (gradMod-- > 0)
		bitsPerGrad[0]++;

	if (m_info->bitperpixel == 16)
	{
		HiColor hi{};
		for (int i = 0; i < 3; i++)
		{
			hi.val <<= bitsPerGrad[i];
			hi.val += color.values[i] >> (BitPerByte - bitsPerGrad[i]);
		}
		for (int i = 0; i < 2; i++)
			bytes[i] = hi.bytes[i];
	}
	else if (m_info->bitperpixel == 24)
	{
		for (int i = 0; i < 3; i++)
			bytes[i] = color.values[i];
	}
	else
		throw std::invalid_argument("Unexpected format");

	return bytes;
}
//------------------------------------------------------------------------------
Color BMP_File::ConvertBytesToColor(std::vector<unsigned char> bytes)
{
	Color color;

	if (m_info->bitperpixel == 16)
	{
		HiColor hi{};
		color.values[0] = (GetBits(bytes[0], 0, 5) << 3);
		color.values[1] = ((GetBits(bytes[0], 5, 3) << 3) + GetBits(bytes[1], 0, 3)) << 2;
		color.values[2] = (GetBits(bytes[1], 3, 5) << 3);
	}
	else if (m_info->bitperpixel == 24)
	{
		for (int i = 0; i < 3; i++)
			color.values[i] = bytes[i];
	}
	else
		throw std::invalid_argument("Unexpected format");

	return color;
}
//------------------------------------------------------------------------------
void BMP_File::CalcError(Color& color, double errorColor[3], double koef)
{
	for (int i = 0; i < 3; i++)
	{
		const int temp = static_cast<double>(color.values[i]) + errorColor[i] * koef;
		color.values[i] = static_cast<unsigned char>(min(max(temp, 0), 255));
	}
}
//------------------------------------------------------------------------------
void BMP_File::SetAllPixelsColor(std::vector<Color> pixelColors)
{
	for (size_t i = 0; i < GetHeight(); i++)
		for (size_t j = 0; j < GetWidth(); j++)
			SetPixelColor(j, i, ConvertBGRToRGB(pixelColors[i * GetWidth() + j]));
}
//------------------------------------------------------------------------------
void BMP_File::SetAllPixelsColorWithErrors(std::vector<Color> pixelColors)
{
	for (size_t i = 0; i < GetHeight(); i++)
		for (size_t j = 0; j < GetWidth(); j++)
		{
			const auto oldColor = pixelColors[i * GetWidth() + j];
			SetPixelColor(j, i, ConvertBGRToRGB(oldColor));
			const auto newColor = ConvertBGRToRGB(GetPixelColor(j, i));

			double errorColor[3] = {};
			
			for (size_t i = 0; i < 3; i++)
				errorColor[i] = (static_cast<double>(newColor.values[i]) - static_cast<double>(oldColor.values[i]));

			if (j < GetWidth() - 1)
			{
				if(i < GetHeight() - 2)
					CalcError(pixelColors[(i + 2) * GetWidth() + j + 1], errorColor, 2.0 / 32.0);

				if (i < GetHeight() - 1)
					CalcError(pixelColors[(i + 1) * GetWidth() + j + 1], errorColor, 4.0 / 32.0);

				CalcError(pixelColors[i * GetWidth() + j + 1], errorColor, 5.0 / 32.0);
			}

			if (j < GetWidth() - 2)
			{
				if (i < GetHeight() - 1)
					CalcError(pixelColors[(i + 1) * GetWidth() + j + 2], errorColor, 2.0 / 16.0);

				CalcError(pixelColors[i * GetWidth() + j + 2], errorColor, 1.0 / 16.0);
			}

			if (i < GetHeight() - 1)
			{
				if (j > 1)
					CalcError(pixelColors[(i + 1) * GetWidth() + j - 2], errorColor, 2.0 / 16.0);

				if (j > 0)
					CalcError(pixelColors[(i + 1) * GetWidth() + j - 1], errorColor, 4.0 / 16.0);

				CalcError(pixelColors[(i + 1) * GetWidth() + j], errorColor, 5.0 / 16.0);
			}

			if (i < GetHeight() - 2)
			{
				if (j > 0)
					CalcError(pixelColors[(i + 2) * GetWidth() + j - 1], errorColor, 2.0 / 16.0);

				CalcError(pixelColors[(i + 2) * GetWidth() + j], errorColor, 3.0 / 16.0);
			}
		}
}
//------------------------------------------------------------------------------