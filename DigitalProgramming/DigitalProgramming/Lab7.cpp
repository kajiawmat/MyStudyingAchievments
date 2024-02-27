#include "Lab7.h"
#include "stdafx.h"
#include "Utils.h"

#define FILE_PATH_PIC_IN    "_ñarib_TC.bmp"
#define FILE_PATH_TXT_IN    "sing.txt"
#define FILE_PATH_PIC_OUT   "_carib_TC_out.bmp"
#define FILE_PATH_TXT_OUT   "sing_out.txt"

void Lab7::Run()
{
    auto bmp_in = new BMP_File(FILE_PATH_PIC_IN);
    FILE* f_in;
    fopen_s(&f_in, FILE_PATH_TXT_IN, "rb");

    if (f_in == nullptr)
        return;

    if (!bmp_in->Init())
        return;

    bmp_in->PrintInfo();

    if (bmp_in->GetBitPerPixel() != 24)
        return;

    auto sizeImage = bmp_in->GetSizeImage();
    fseek(f_in, 0, SEEK_END);
    auto txtSize = ftell(f_in);
    fseek(f_in, 0, SEEK_SET);

    if (txtSize > sizeImage)
        return;

    const auto koef = (double)txtSize / sizeImage;

    int bitsForText = 0;

    if (koef < 0.25)
        bitsForText = 2;
    else if (koef < 0.5)
        bitsForText = 4;
    else if (koef < 0.75)
        bitsForText = 6;
    else
        bitsForText = 8;

    printf("%f\n", koef);

    unsigned long long count = 0;
    auto pixels = bmp_in->GetPixels();

    while (!feof(f_in))
    {
        unsigned char byte = 0;
        fread(&byte, 1, 1, f_in);

        for (int i = 0; i < BitPerByte / bitsForText; i++)
        {
            auto& p_byte = pixels[count / pixels[0].size()][count % pixels[0].size()];
            p_byte = SetBits(p_byte, BitPerByte - bitsForText, bitsForText, GetBits(byte, i * bitsForText, bitsForText));
            count++;
        }
    }

    bmp_in->SetPixels(pixels);
    bmp_in->Write(FILE_PATH_PIC_OUT);

    FILE* f_out;
    fopen_s(&f_out, FILE_PATH_TXT_OUT, "wb");

    if (f_out == nullptr)
        return;

    count = 0;

    while (count < bmp_in->GetSizeImage())
    {
        unsigned char byte = 0;

        for (int i = 0; i < BitPerByte / bitsForText; i++)
        {
            auto p_byte = pixels[count / pixels[0].size()][count % pixels[0].size()];
            byte = SetBits(byte, i * bitsForText, bitsForText, GetBits(p_byte, BitPerByte - bitsForText, bitsForText));
            count++;
        }
        fwrite(&byte, 1, 1, f_out);
    }

    fclose(f_in);
    fclose(f_out);
}