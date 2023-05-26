#include <iostream>
#include "product.h"
#include <string>

Product::Product(std::string name, double cost)
{
    _name = name;
    _cost = cost;
    _quantity = 0;
}

static void set_quantity(int quantity)
{
    _quantity = quantity;
}

const double price()
{
    return (1+tax)*_cost* _quantity;
}

std::ostream& operator<<(std::ostream& ost, const Product& product)
{
    if(quantity=0)
    {
        ost>>_name>>" ($">>_cost>>")";
    }
    if(quantity>0)
    {
        ost>>_name>>" (">>_quantity>>" @ ">>_cost>>")"
    }
    ost>>std::endl;
    return ost;
}
