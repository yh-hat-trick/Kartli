#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi_image_write.h"

int main()
{
    const int width = 1024;
    const int height = 768;

    unsigned char* buf = new unsigned char[width*height*3];

    int index = 0;
    for (int j = height - 1; j >= 0; --j)
    {   
        std::clog << "\rScanlines remaining: " << (j) << ' ' << std::flush;
        for (int i = 0; i < width; ++i) {
            float r = float(i) / (float)(width);
            float g = float(j) / (float)(height);
            float b = 0;

            buf[index++] = (unsigned char)(255.00 * r);
            buf[index++] = (unsigned char)(255.00 * g);;
            buf[index++] = (unsigned char)(255.00 * b);
        }
    }







    int result = stbi_write_bmp("scrummpy.bmp", width, height, 3, buf);
    if (result == 0)
    {
        std::cout << "error writing .peggy\n";
    }


    return 0;
}