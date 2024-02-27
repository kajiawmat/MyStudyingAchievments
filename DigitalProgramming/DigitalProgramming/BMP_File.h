#pragma once
#pragma pack (1)

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Structs.h"

class BMP_File
{
public:
    BMP_File(std::string filename);
    BMP_File(std::vector< std::vector<unsigned char> > pixels);

    bool    Init();
    bool    Reset();
    void    Write(std::string filename);

    void    PrintInfo();
    void    PrintPalitra();
    void    PrintPixels();

    void    SetFilename(std::string filename) { m_filename = filename; }

    unsigned long   GetWidth() { return m_info->width; }
    unsigned long   GetHeight() { return m_info->height; }

    unsigned long   GetSizeImage() { return m_info->sizeimage; }

    unsigned short  GetColorTableSize() { return (m_info->bm_offset - sizeof(*m_info)) / 4; }

    void            SetBitPerPixel(unsigned short bitperpixel, bool useDithering = true);
    unsigned short  GetBitPerPixel() { return m_info->bitperpixel; }

    std::vector<Color> GetPalitra() { return m_palitra; }

    void    SetPixels(std::vector< std::vector<unsigned char> > pixels);
    std::vector< std::vector<unsigned char> >  GetPixels() { return m_pixels; }

    void            SetPalitraColor(int ind, Color color);
    const Color     GetPalitraColor(int ind);

    void            SetPixelColor(int x, int y, Color color);
    const Color     GetPixelColor(int x, int y);

    void    InsertPixelRowInto(int pixel_ind);
    void    InsertPixelColumnInto(int pixel_ind);

private:
    struct Info {
        unsigned short id;
        unsigned long  f_size;
        unsigned short rez1, rez2;
        unsigned long  bm_offset;
        unsigned long  h_size;
        long  width;
        long  height;
        unsigned short planes;
        unsigned short bitperpixel;
        unsigned long  compression;
        unsigned long  sizeimage;
        unsigned long  hres;
        unsigned long  vres;
        unsigned long  clrused;
        unsigned long  clrimp;
    };

    std::string m_filename;

    Info* m_info;

    std::vector<Color> m_palitra;
    std::vector< std::vector<unsigned char> > m_pixels;

    bool    ReadFile(FILE* file);
    bool    ReadInfo(FILE* file);
    bool    ReadPalitra(FILE* file);
    bool    ReadPixels(FILE* file);

    unsigned long   GetRowLength();
    unsigned long   GetPadding();
    unsigned long   GetColorTableMaxSize();
    
    void    UpdateImageProperties();

    unsigned short      GetPalitraIndOfColor(Color color);
    unsigned long long  GetDiffColor(Color x, Color y);

    std::vector<unsigned char>  ConvertColorToBytes(Color color);
    Color ConvertBytesToColor(std::vector<unsigned char> bytes);

    void    CalcError(Color& color, double errorColor[3], double koef);

    void    SetAllPixelsColor(std::vector<Color> pixelColors);
    void    SetAllPixelsColorWithErrors(std::vector<Color> pixelColors);
};

