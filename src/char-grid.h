#pragma once

#include <stdint.h>
#include <cstddef>
#include <string>
#include <iostream>

#define ALIGN_HORIZONTAL_LEFT 0b00000001
#define ALIGN_HORIZONTAL_MIDDLE 0b00000010
#define ALIGN_HORIZONTAL_RIGHT 0b00000100
#define ALIGN_VERTICAL_TOP 0b00010000
#define ALIGN_VERTICAL_MIDDLE 0b00100000
#define ALIGN_VERTICAL_BOTTOM 0b01000000

class CharGrid
{
    private:
        size_t width;
        size_t height;
        unsigned char * c;
    public:
        CharGrid(size_t width, size_t height);
        ~CharGrid();
        
        unsigned char * at(size_t x, size_t y);
        size_t getWidth();
        size_t getHeight();

        std::string toString();

};

CharGrid * resize(CharGrid * grid, size_t width, size_t height, int alignMethod, unsigned char emptyChar);

CharGrid * sumVertically(CharGrid * topGrid, CharGrid * bottomGrid);
CharGrid * sumHorizontally(CharGrid * leftGrid, CharGrid * rightGrid);

CharGrid * sumVertically(CharGrid * topGrid, CharGrid * bottomGrid, int alignMethod, unsigned char emptyChar);
CharGrid * sumHorizontally(CharGrid * leftGrid, CharGrid * rightGrid, int alignMethod, unsigned char emptyChar);
