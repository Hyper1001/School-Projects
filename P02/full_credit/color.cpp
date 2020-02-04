#include <iostream>
#include "color.h"
#include <string>


Color::Color(int r, int g, int b) : red{r}, green {g}, blue{b}
{
    if(r>255)
        red = 255;
    else if(r<0)
        red=0;
    if(g>255)
        green = 255;
    else if(g<0)
        green=0;
    if(b>255)
        blue = 255;
    else if(b<0)
        blue=0;
}

std::string Color::to_string()
{
    return "("+std::to_string(red)+", "+std::to_string(green)+", "+std::to_string(blue)+")";
}

std::string Color::colorize(std::string text)
{
    return "\033[38;2;"+std::to_string(red)+";"+std::to_string(green)+";"+std::to_string(blue)+"m"+text+"\033[0m";
}
