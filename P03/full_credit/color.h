    #ifndef __COLOR_H
#define __COLOR_H
#include <string>

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
    friend ostream& operator<<(ostream& ost, const Color& color)
    friend istream& operator>>(istream& ist, Color& color)
};

#endif
