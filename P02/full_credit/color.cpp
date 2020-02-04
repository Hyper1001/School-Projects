#include <iostream>
#include "color.h"
#include <string>


Color::Color(int r, int g, int b) : _red{r}, _green {g}, _blue{b}
{
    if(r>255)
        _red = 255;
    else if(r<0)
        _red=0;
    if(g>255)
        _green = 255;
    else if(g<0)
        _green=0;
    if(b>255)
        _blue = 255;
    else if(b<0)
        _blue=0;
}

std::string Color::to_string()
{
    return "("+std::to_string(_red)+", "+std::to_string(_green)+", "+std::to_string(_blue)+")";
}

std::string Color::colorize(std::string text)
{
    return "\033[38;2;"+std::to_string(_red)+";"+std::to_string(_green)+";"+std::to_string(_blue)+"m"+text+"\033[0m";
}
