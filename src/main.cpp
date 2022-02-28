#include <iostream>

#include "tree.h"

using namespace std;

int main() {
    size_t n;
    cin >> n;
    size_t * sizes = new size_t [n];

    for (size_t i = 0; i < n; ++i) {
        cin >> sizes[i];
    }

    CharGrid * grid = createForest(n, sizes);
    cout << grid->toString() << endl;

    delete sizes, grid;
    return 0;
}
