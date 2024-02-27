#include "Lab3.h"

#define FILE_PATH_IN  "_ñarib_TC.bmp"
#define FILE_PATH_OUT "_ñarib_TC_turned.BMP"


void Lab3::Run()
{
    auto bmp = new BMP_File(FILE_PATH_IN);

    if (!bmp->Init())
        return;

    bmp->PrintInfo();

    auto pixels = bmp->GetPixels();

    if (pixels.size() == 0)
        return;

    const int bytePerPixel = std::max(bmp->GetBitPerPixel() / 8, 1);

    std::vector<std::vector<unsigned char> > new_pixels(pixels[0].size() / bytePerPixel);

    for (auto& new_row : new_pixels)
        new_row.resize(pixels.size() * bytePerPixel);

    for (size_t i = 0; i < new_pixels.size(); i++)
    {
        auto& new_row = new_pixels[i];
        auto const new_width = new_row.size() / bytePerPixel;
        for (size_t j = 0; j < new_width; j++)
        {
            for (size_t k = 0; k < bytePerPixel; k++)
            {
                new_row[bytePerPixel * j + k] = pixels[new_width - j - 1][bytePerPixel * i + k];
            }
        }
    }

    bmp->SetPixels(new_pixels);
    bmp->PrintInfo();
    bmp->Write(FILE_PATH_OUT);
}