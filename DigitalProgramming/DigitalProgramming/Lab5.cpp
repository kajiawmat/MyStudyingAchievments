#include "Lab5.h"
#include "stdafx.h"

#define FILE_PATH_IN  "CAT256.BMP"
#define FILE_PATH_OUT "_ñarib_TC_turned.BMP"

const float koef = 0.3;

void Lab5::Run()
{
    auto bmp = new BMP_File(FILE_PATH_IN);

    if (!bmp->Init())
        return;

    bmp->PrintInfo();

    initwindow(bmp->GetWidth() * koef, bmp->GetHeight() * koef);
    for (size_t i = 0; i < bmp->GetHeight() * koef; i++)
    {
        for (size_t j = 0; j < bmp->GetWidth() * koef; j++)
        {
            auto color = bmp->GetPixelColor(j / koef, i / koef).values;
            putpixel(j, bmp->GetHeight() * koef - i, RGB(color[0], color[1], color[2]));
        }
    }
    int a;
    std::cin >> a;
    closegraph();

    /*auto palitra = bmp->GetPalitra();
    auto pixels = bmp->GetPixels();

    if (pixels.size() == 0)
        return;

    const int bytePerPixel = bmp->GetBitPerPixel() / 8;
    const bool usePalitra = bmp->GetBitPerPixel() <= 8;

    initwindow(bmp->GetWidth()*koef, bmp->GetHeight()*koef);
    for (size_t i = 0; i < pixels.size() * koef; i++)
    {
        auto& row = pixels[(size_t)(i / koef)];

        if (usePalitra)
        {
            for (size_t j = 0; j < row.size() * koef; j++)
            {
                auto& color = palitra[row[(size_t)(j / koef)]];
                putpixel(j, bmp->GetHeight() * koef - i, RGB(color.values[2], color.values[1], color.values[0]));
            }
        }
        else
        {
            for (size_t j = 0; j < row.size() * koef; j += bytePerPixel)
            {
                size_t pixelInd = (size_t)(j / bytePerPixel / koef) * bytePerPixel;
                putpixel(j / bytePerPixel, bmp->GetHeight() * koef - i, RGB(row[pixelInd+2], row[pixelInd+1], row[pixelInd]));
            }
        }
    }
    int a;
    std::cin >> a;
    closegraph();*/
}