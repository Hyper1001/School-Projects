#include "options.h"
#include <string>
#include <iostream>

Options::Options(std::string name, double cost)
{
    _name = name;
    _cost = cost;
}

Options::~Options() {}

double Options::cost()
{
    return _cost;
}

std::string Options::to_string()
{
    return _name + ": $" + std::to_string(_cost);
}
