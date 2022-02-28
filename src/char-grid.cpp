#include "char-grid.h"

CharGrid::CharGrid(size_t width, size_t height) {
    this->c = new unsigned char [width*height];
    this->width = width;
    this->height = height;
}

CharGrid::~CharGrid() {
    delete c;
}

unsigned char * CharGrid::at(size_t x, size_t y) {
    size_t pos = y * width + x;
    if (pos >= width * height) {
        return nullptr;
    } else {
        return &(c[pos]);
    }
}

size_t CharGrid::getWidth() {
    return width;
}
size_t CharGrid::getHeight() {
    return height;
}

std::string CharGrid::toString() {
    std::string result;
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            result.push_back(*at(x,y));
        }
        result.push_back('\n');
    }
    return result;
}

CharGrid * resize(CharGrid * grid, size_t width, size_t height, int alignMethod, unsigned char emptyChar) {
    CharGrid * newGrid = new CharGrid(width, height);
    size_t oldWidth = grid->getWidth();
    size_t oldHeight = grid->getHeight();
    if (width < oldWidth || height < oldHeight) {
        throw "resize to smaller grid does not supported yet";
    }
    size_t x_addition;
    size_t y_addition;
    if ((alignMethod & ALIGN_HORIZONTAL_LEFT) == ALIGN_HORIZONTAL_LEFT) {
        x_addition = 0;
    } else if ((alignMethod & ALIGN_HORIZONTAL_RIGHT) == ALIGN_HORIZONTAL_RIGHT) {
        x_addition = width-oldWidth;
    } else {
        x_addition = (width-oldWidth) / 2;
    }
    if ((alignMethod & ALIGN_VERTICAL_TOP) == ALIGN_VERTICAL_TOP) {
        y_addition = 0;
    } else if ((alignMethod & ALIGN_VERTICAL_BOTTOM) == ALIGN_VERTICAL_BOTTOM) {
        y_addition = height-oldHeight;
    } else {
        y_addition = (height-oldHeight) / 2;
    }
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            *newGrid->at(x, y) = emptyChar;
        }
    }
    for (size_t x = 0; x < oldWidth; ++x) { // TODO change y to x to optimize
        for (size_t y = 0; y < oldHeight; ++y) {
            unsigned char * c = newGrid->at(x+x_addition,y+y_addition);
            unsigned char oldC = *grid->at(x,y);
            c[0] = oldC;
            //std::cout << oldC << " and " << c[0] << std::endl;
        }
    }
    return newGrid;
}

CharGrid * sumVertically(CharGrid * topGrid, CharGrid * bottomGrid) {
    if (topGrid->getWidth() != bottomGrid->getWidth()) {
        throw "cannot sum grids with different widths";
    }
    size_t width = topGrid->getWidth();
    size_t topHeight = topGrid->getHeight();
    size_t height = topHeight + bottomGrid->getHeight();

    CharGrid * newGrid = new CharGrid (width, height);
    for (size_t y = 0; y < topHeight; ++y) {
        for (size_t x = 0; x < width; ++x) {
            *newGrid->at(x,y) = *topGrid->at(x,y);
        }
    }
    for (size_t y = 0; y < bottomGrid->getHeight(); ++y) {
        for (size_t x = 0; x < width; ++x) {
            *newGrid->at(x,y+topHeight) = *bottomGrid->at(x,y);
        }
    }
    return newGrid;
}

CharGrid * sumHorizontally(CharGrid * leftGrid, CharGrid * rightGrid) {
    if (leftGrid->getHeight() != rightGrid->getHeight()) {
        throw "cannot sum grids with different heights";
    }
    size_t height = leftGrid->getHeight();
    size_t leftWidth = leftGrid->getWidth();
    size_t width = leftWidth + rightGrid->getWidth();

    CharGrid * newGrid = new CharGrid (width, height);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < leftWidth; ++x) {
            *newGrid->at(x,y) = *leftGrid->at(x,y);
        }
    }
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < rightGrid->getWidth(); ++x) {
            *newGrid->at(x+leftWidth,y) = *rightGrid->at(x,y);
        }
    }
    return newGrid;
}

CharGrid * sumVertically(CharGrid * topGrid, CharGrid * bottomGrid, int alignMethod, unsigned char emptyChar) {
    CharGrid * answer;
    if (topGrid->getWidth() < bottomGrid->getWidth()) {
        CharGrid * alterTopGrid = resize(topGrid, bottomGrid->getWidth(), topGrid->getHeight(), alignMethod, emptyChar);
        answer = sumVertically(alterTopGrid, bottomGrid);
        delete alterTopGrid;
    } else if (topGrid->getWidth() > bottomGrid->getWidth()) {
        CharGrid * alterBottomGrid = resize(bottomGrid, topGrid->getWidth(), bottomGrid->getHeight(), alignMethod, emptyChar);
        answer = sumVertically(topGrid, alterBottomGrid);
        delete alterBottomGrid;
    } else {
        answer = sumVertically(topGrid, bottomGrid);
    }
    return answer;
}

CharGrid * sumHorizontally(CharGrid * leftGrid, CharGrid * rightGrid, int alignMethod, unsigned char emptyChar) {
    CharGrid * answer;
    if (leftGrid->getHeight() < rightGrid->getHeight()) {
        CharGrid * alterLeftGrid = resize(leftGrid, leftGrid->getWidth(), rightGrid->getHeight(), alignMethod, emptyChar);
        answer = sumHorizontally(alterLeftGrid, rightGrid);
        delete alterLeftGrid;
    } else if (leftGrid->getHeight() > rightGrid->getHeight()) {
        CharGrid * alterRightGrid = resize(rightGrid, rightGrid->getWidth(), leftGrid->getHeight(), alignMethod, emptyChar);
        answer = sumHorizontally(leftGrid, alterRightGrid);
        delete alterRightGrid;
    } else {
        answer = sumHorizontally(leftGrid, rightGrid);
    }
    return answer;
}
