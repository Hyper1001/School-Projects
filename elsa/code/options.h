#ifndef __OPTIONS_H
#define __OPTIONS_H
#include <iostream>
#include <string>
class Options
{
protected:
    std::string _name;
    double _cost;
public:
    Options(std::string name,double cost);
    ~Options();
    double cost();
    std::string to_string();
};
#endif
