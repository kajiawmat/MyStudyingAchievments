#include "Lab4.h"
#include "stdafx.h"

#define FILE_PATH_IN  "CAT4.BMP"

void Lab4::Run()
{
    auto bmp = new BMP_File(FILE_PATH_IN);

    if (!bmp->Init())
        return;

    bmp->PrintInfo();

    initwindow(bmp->GetWidth(), bmp->GetHeight());
    for (size_t i = 0; i < bmp->GetHeight(); i++)
    {
        for (size_t j = 0; j < bmp->GetWidth(); j++)
        {
            auto color = bmp->GetPixelColor(j, i).values;
            putpixel(j, bmp->GetHeight() - i, RGB(color[0], color[1], color[2]));
        }
    }
    int a;
    std::cin >> a;
    closegraph();
}