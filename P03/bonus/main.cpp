#include "color.h"
#include <iostream>

int main() {
    Color red{255,0,0};
    Color green{0,255,0};
    Color blue{0,0,255};
    std::cout << red.colorize("Red") << std::endl;
    std::cout << green.colorize("Green") << std::endl;
    std::cout << blue.colorize("Blue") << std::endl;
    int r;
    std::cout<<"Please enter a RGB for red: ";
    std::cin>>r;
    int g;
    std::cout<<"Please enter a RGB for green: ";
    std::cin>>g;
    int b;
    std::cout<<"Please enter a RGB for blue: ";
    std::cin>>b;
    Color creation{r,g,b};
    std::cout<<creation.colorize(creation.to_string())<<std::endl;
}
