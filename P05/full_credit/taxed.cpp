#include <iostream>
#include "taxed.h"
#include <string>

Taxed::Taxed(std::string name, double cost):Product(name,cost)
{
    _tax = 0.0825;
}

static void set_tax_rate(double sales_tax)
{
    _tax = sales_tax;
}

const double price()
{
    return (1+tax)*_cost* _quantity;
}
