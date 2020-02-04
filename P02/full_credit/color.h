#ifndef __COLOR_H
#define __COLOR_H
#include <string>

class Color
{
    int red;
    int green;
    int blue;
public:
    Color(int r,int g, int b);
    std::string to_string();
    std::string colorize(std::string text);
};

#endif
