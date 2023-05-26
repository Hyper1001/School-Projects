#include "cart.h"

Cart::Cart(std::string customer)
{
    _customer = customer;
    _items;
}

Cart::~Cart()
{
    for(auto i:_items)
    {
        delete i; //delete all items in vectors so no memory left over
    }
}
//comment
Cart::Cart(const Cart& cart)
{
    _customer = cart._customer;
    for(auto i:cart._items)
    {
        _items.push_back(new Item{*i}); //push onto vector
    }
}

void Cart::add_item(Item& item)
{
    _items.push_back(new Item{item}); //push onto vector
}

double Cart::cost()
{
    double price;
    for(auto i:_items)
    {
        price = price + i->cost(); //price starts at 0, will add cost from each item in the vector
    }
    return price;
}

std::vector<Item*>::iterator Cart::begin()
{
	return _items.begin();
}

std::vector<Item*>::iterator Cart::end()
{
    return _items.end();
}
