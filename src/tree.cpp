#include "tree.h"

CharGrid * createTreePart(size_t size) {
    if (size <= 0) {
        throw "tree part cannot be zero or smaller";
    }
    size_t width = size * 2 - 1;
    size_t height = size;
    CharGrid * grid = new CharGrid (width, height);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            if (abs(width/2 - x) <= y) {
                *grid->at(x,y) = '*';
            } else {
                *grid->at(x,y) = ' ';
            }
        }
    }
    return grid;
}

CharGrid * createTree(size_t size) {
    if (size <= 0) {
        throw "cannot generate tree with size <= 0";
    }
    if (size == 1) {
        return createTreePart(1);
    }
    CharGrid * grid = createTreePart(2);
    for (size_t i = 3; i <= size; ++i) {
        CharGrid * newPartGrid = createTreePart(i);
        CharGrid * newGrid = sumVertically(grid, newPartGrid, ALIGN_HORIZONTAL_MIDDLE, ' ');
        delete grid;
        delete newPartGrid;
        grid = newGrid;
    }
    return grid;
}

CharGrid * createForest(size_t count, size_t * sizes) {
    if (count <= 0) {
        throw "cannot generate empty forest";
    }
    CharGrid * grid = createTree(sizes[0]);
    for (size_t i = 1; i < count; ++i) {
        CharGrid * newTreeGrid = createTree(sizes[i]);
        CharGrid * newGrid = sumHorizontally(grid, newTreeGrid, ALIGN_VERTICAL_BOTTOM, ' ');
        delete grid;
        delete newTreeGrid;
        grid = newGrid;
    }
    return grid;
}
