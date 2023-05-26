#include "item.h"
#include <iomanip>

Item::Item(std::string name, double price)
{
    _name = name;
    _price = price;
}

double Item::cost()
{
    return _price;
}

std::ostream& operator<<(ostream& ost, const Item& item)
{
    ost<<std::fixed<<std::setprecision(2)<<"$\t"<<item._price;<<"\t"<<item._name;
}

std::istream& operator>>(istream& ost, const Item& item)
{

    //test to see if the price entered is valid and throw a runtime error if it isn't.
    throw std::runtime_error{"Invalid price: 'item name' ==> 'incorrect price given'"};
    return ist;
}
