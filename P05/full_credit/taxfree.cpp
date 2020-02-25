#include <iostream>
#include "taxfree.h"
#include <string>

Taxfree::Taxfree(std::string name, double cost):Product(name,cost)
{
}

const double price()
{
    return _quantity*_cost;
}
