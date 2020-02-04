// This main program can be used to test your class.
// **You must COMPLETE both color.h and color.cpp before compiling this!**
// Then, the provided Makefile will build it for you if you type 'make test'.

#include "color.h"
#include <iostream>

int main() {
    Color red{255,0,0};
    Color green{0,255,0};
    Color blue{0,0,255};
    std::cout << red.colorize("Red") << std::endl;
    std::cout << green.colorize("Green") << std::endl;
    std::cout << blue.colorize("Blue") << std::endl;
}
