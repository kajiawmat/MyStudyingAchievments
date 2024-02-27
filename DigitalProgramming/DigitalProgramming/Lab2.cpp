#include "Lab2.h"

#define FILE_PATH_IN  "_ñarib_TC.bmp"
#define FILE_PATH_OUT "_carib_TC_bordered_2.BMP"

#define BORDER_WIDTH 15

void Lab2::Run()
{
    auto bmp = new BMP_File(FILE_PATH_IN);

    if (!bmp->Init())
        return;
    
    bmp->PrintInfo();

    const int maxRandValue = 255;

    for (size_t i = 0; i < BORDER_WIDTH; i++)
    {
        bmp->InsertPixelColumnInto(0);
        for (size_t j = 0; j < bmp->GetHeight(); j++)
        {
            Color color;
            for (size_t k = 0; k < 3; k++)
                color.values[k] = rand() % maxRandValue;

            bmp->SetPixelColor(0, j, color);
        }
    }

    for (size_t i = 0; i < BORDER_WIDTH; i++)
    {
        bmp->InsertPixelColumnInto(bmp->GetWidth());
        for (size_t j = 0; j < bmp->GetHeight(); j++)
        {
            Color color;
            for (size_t k = 0; k < 3; k++)
                color.values[k] = rand() % maxRandValue;

            bmp->SetPixelColor(bmp->GetWidth() - 1, j, color);
        }
    }

    for (size_t i = 0; i < BORDER_WIDTH; i++)
    {
        bmp->InsertPixelRowInto(0);
        for (size_t j = 0; j < bmp->GetWidth(); j++)
        {
            Color color;
            for(size_t k=0;k<3;k++)
                color.values[k] = rand() % maxRandValue;

            bmp->SetPixelColor(j, 0, color);
        }
    }

    for (size_t i = 0; i < BORDER_WIDTH; i++)
    {
        bmp->InsertPixelRowInto(bmp->GetHeight());
        for (size_t j = 0; j < bmp->GetWidth(); j++)
        {
            Color color;
            for (size_t k = 0; k < 3; k++)
                color.values[k] = rand() % maxRandValue;

            bmp->SetPixelColor(j, bmp->GetHeight() - 1, color);
        }
    }

    bmp->PrintInfo();
    bmp->Write(FILE_PATH_OUT);
}
