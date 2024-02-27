#include "Converter.h"
#include "stdafx.h"

using namespace std;

//------------------------------------------------------------------------------
void Converter::ConvertFromPCXToBMP(std::string filename1, std::string filename2, unsigned short bitPerPixel)
{
    auto pcx = new PCX_File(filename1);

    if (!pcx->Init())
        return;

    pcx->PrintInfo();

    auto pcx_pixels = pcx->GetPixelColors();

    auto bmp_pixels = vector< vector<unsigned char> >(pcx->GetHeight());

    for (size_t i = 0; i < pcx->GetHeight(); i++)
    {
        bmp_pixels[i] = vector<unsigned char>(pcx->GetWidth() * 3);
        for (size_t j = 0; j < pcx->GetWidth(); j++)
        {
            auto color = pcx->GetPixelColor(pcx->GetHeight() - (i + 1), j);
            for (size_t k = 0; k < 3; k++)
                bmp_pixels[i][j * 3 + k] = color.values[2 - k];
        }
    }

    auto bmp = new BMP_File(bmp_pixels);

    bmp->PrintInfo();
    bmp->SetBitPerPixel(bitPerPixel, true);
    bmp->PrintInfo();

    bmp->Write(filename2);
}
//------------------------------------------------------------------------------
void Converter::ConvertFromBMPToBMP(std::string filename1, std::string filename2, unsigned short bitPerPixel)
{
    auto bmp = new BMP_File(filename1);

    if (bmp->Init())
        return;

    bmp->SetBitPerPixel(bitPerPixel, true);
    bmp->PrintInfo();

    bmp->Write(filename2);
}
//------------------------------------------------------------------------------