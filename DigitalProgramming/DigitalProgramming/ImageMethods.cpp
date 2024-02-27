#include "ImageMethods.h"
#include <algorithm>

using namespace std;

Color ConvertBGRToRGB(Color color)
{
    swap(color.values[0], color.values[2]);
    return color;
}
//------------------------------------------------------------------------------
void DeterminePrimaryColor(vector<Color>& box, Color& color)
{
    int indMax = 0;
    for (int i = 0; i < 3; i++)
    {
        unsigned short maxVal = max_element(box.begin(), box.end(), [i](Color& x, Color& y) { return x.values[i] < y.values[i]; })->values[i];
        unsigned short minVal = min_element(box.begin(), box.end(), [i](Color& x, Color& y) { return x.values[i] < y.values[i]; })->values[i];

        color.values[i] = maxVal - minVal;

        if (color.values[i] > color.values[indMax])
            indMax = i;
    }

    sort(box.begin(), box.end(), [indMax](Color& x, Color& y) { return x.values[indMax] < y.values[indMax]; });
}
//------------------------------------------------------------------------------
vector<Color> MedianCutPalette(const vector< vector<Color> >& pixels, uint8_t numColors)
{
    std::vector<Color> new_pixels;
    for (int i = 0; i < pixels.size(); i++)
        new_pixels.insert(new_pixels.end(), pixels[i].begin(), pixels[i].end());

    return MedianCutPalette(new_pixels, numColors);
}
//------------------------------------------------------------------------------
vector<Color> MedianCutPalette(const vector<Color> &pixels, uint8_t numColors)
{
    typedef vector<Color> Box;
    typedef pair<uint8_t, Box> RangeBox;

    vector<RangeBox> boxes;
    Box init = pixels;
    boxes.push_back(RangeBox(0, init));

    while (boxes.size() < numColors)
    {
        for (auto& boxData : boxes)
        {
            Color color = Color();
            DeterminePrimaryColor(get<1>(boxData), color);
            get<0>(boxData) = *max_element(color.values, next(color.values, 3));
        }

        sort(boxes.begin(), boxes.end(), [](RangeBox& x, RangeBox& y) { return get<0>(x) < get<0>(y); });

        vector<RangeBox>::iterator it = prev(boxes.end());
        Box biggestBox = get<1>(*it);
        boxes.erase(it);

        Box splitA(biggestBox.begin(), biggestBox.begin() + biggestBox.size() / 2);
        Box splitB(biggestBox.begin() + biggestBox.size() / 2, biggestBox.end());

        boxes.push_back(RangeBox(0, splitA));
        boxes.push_back(RangeBox(0, splitB));
    }

    vector<Color> palette;
    for (const RangeBox& boxData : boxes)
    {
        Box box = std::get<1>(boxData);
        uint32_t colorVals[3] = {};
        
        for (auto v_box : box)
        {
            for (int i = 0; i < 3; i++)
                colorVals[i] += v_box.values[i];
        }

        Color color = Color();
        for (int i = 0; i < 3; i++)
            color.values[i] = static_cast<unsigned char>(colorVals[i] / static_cast<uint32_t>(box.size()));

        palette.push_back(color);
    }
    return palette;
}
