#include "color.h"
#include <iostream>

int main() {
    Color red{255,0,0};
    Color green{0,255,0};
    Color blue{0,0,255};
    Color reset();
    std::cout << red << "This is red text " << green << "this is green text"<< blue << ", and this is blue text." << reset << std::endl;
    Color creation{};
    std::cin>>creation;
    std::cout<<creation<<creation.to_string()<<std::endl;
}
