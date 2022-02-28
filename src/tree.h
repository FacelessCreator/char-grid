#pragma once

#include "char-grid.h"
#include <cstdlib>

CharGrid * createTreePart(size_t size);
CharGrid * createTree(size_t size);

CharGrid * createForest(size_t count, size_t * sizes);
