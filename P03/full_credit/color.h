#ifndef __COLOR_H
#define __COLOR_H
#include <string>
#include <ostream>
class Color
{
private:
    int _red;
    int _green;
    int _blue;
    bool _reset;
public:
    Color();
    Color(int r,int g, int b);
    std::string to_string();
    friend std::ostream& operator<<(std::ostream& ost, const Color& color);
    friend std::istream& operator>>(std::istream& ist, Color& color);
};

#endif
