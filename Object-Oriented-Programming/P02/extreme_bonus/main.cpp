#include "color.h"
#include <iostream>
#include <vector>

int main() {
    Color red{255,0,0};
    Color green{0,255,0};
    Color blue{0,0,255};
    std::vector<Color> colors;
    colors.push_back(*red);
    colors.push_back(*green);
    colors.push_back(*blue);
}
