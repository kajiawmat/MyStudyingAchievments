#include "RGR.h"
#include "stdafx.h"
#include "ImageMethods.h"
#include "Converter.h"

#define FILE_PATH_IN "CAT256.PCX"
#define FILE_PATH_OUT "CAT16_dithering.BMP"

#define BIT_PER_PIXEL 4

void RGR::Run()
{
    auto converter = Converter();
    converter.ConvertFromPCXToBMP(FILE_PATH_IN, FILE_PATH_OUT, BIT_PER_PIXEL);
}
