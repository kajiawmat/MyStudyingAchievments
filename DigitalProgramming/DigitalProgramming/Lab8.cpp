#include "Lab8.h"
#include "stdafx.h"

#define FILE_PATH_IN  "CAT256.PCX"

void Lab8::Run()
{
    auto pcx = new PCX_File(FILE_PATH_IN);

    if (!pcx->Init())
        return;

    pcx->PrintInfo();

    initwindow(pcx->GetWidth(), pcx->GetHeight());

    for (size_t i = 0; i < pcx->GetHeight(); i++)
    {
        for (size_t j = 0; j < pcx->GetWidth(); j++)
        {
            auto color = pcx->GetPixelColor(i, j).values;
            putpixel(j, i, RGB((int)color[0], (int)color[1], (int)color[2]));
        }
    }
    getch();
    closegraph();
}
