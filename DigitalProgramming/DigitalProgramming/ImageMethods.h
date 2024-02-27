#pragma once
#include "Structs.h"
#include <iostream>
#include <vector>

Color ConvertBGRToRGB(Color color);

std::vector<Color> MedianCutPalette(const std::vector< std::vector<Color> >& pixels, uint8_t numColors);
std::vector<Color> MedianCutPalette(const std::vector<Color> &pixels, uint8_t numColors);