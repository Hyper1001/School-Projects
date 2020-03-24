#include "order.h"
#include <vector>
#include <iostream>

Order::Order(Customer& customer)
{
    _customer = customer;
}

Order::~Order() {}

int Order::add_product(Desktop& desktop)
{
    _products.push_back(&desktop);
    return _products.size()-1;
}

double Order::price()
{
    double total = 0;
    for(int i =0;i<_products.size())
    {
        total+= _products[i]->cost;
    }
    return total;
}

std::ostream& operator<<(std::ostream& ost, const Order& order)
{
    ost<<order._customer << " $"<<order.price();
}
