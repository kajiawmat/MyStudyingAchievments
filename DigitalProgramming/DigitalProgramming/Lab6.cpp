#include "Lab6.h"
#include "stdafx.h"

#define FILE_PATH_IN  "CAT256.BMP"
#define FILE_PATH_LOGO "logo.bmp"

const unsigned char BackgroundColor[] = { 255,255,255 };
const float koef = 0.5f;

void Lab6::Run()
{
    auto bmp_in = new BMP_File(FILE_PATH_IN);

    if (!bmp_in->Init())
        return;

    bmp_in->PrintInfo();

    auto bmp_logo = new BMP_File(FILE_PATH_LOGO);

    if (!bmp_logo->Init())
        return;

    bmp_logo->PrintInfo();

    initwindow(bmp_in->GetWidth(), bmp_in->GetHeight());
    for (size_t i = 0; i < bmp_in->GetHeight(); i++)
    {
        for (size_t j = 0; j < bmp_in->GetWidth(); j++)
        {
            auto color_in = bmp_in->GetPixelColor(j, i).values;
            unsigned char color[3] = { color_in[0], color_in[1], color_in[2] };

            if (i < bmp_logo->GetHeight() && j < bmp_logo->GetWidth())
            {
                auto temp_color = bmp_logo->GetPixelColor(j, i).values;

                if (!(temp_color[0] == BackgroundColor[0] && temp_color[1] == BackgroundColor[1] && temp_color[2] == BackgroundColor[2]))
                    for (int k = 0; k < 3; k++)
                        color[k] = color[k] * (1.f - koef) + temp_color[k] * koef;
            }

            putpixel(j, bmp_in->GetHeight() - i, RGB(color[0], color[1], color[2]));
        }
    }
    int a;
    std::cin >> a;
    closegraph();
}