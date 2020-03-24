#include "store.h"
#include <iostream>
#include <vector>
#include <string>

void Store::add_customer(Customer& customer)
{
    customers.push_back(customer);
}

int Store::num_customers()
{
    return customers.size();
}

Customer& Store::customer(int index)
{
    return customers.at(index);
}

void add_option(Options& option)
{
    options.push_back(option); //can't figure out why this breaks
}

int Store::num_options()
{
    return options.size();
}

Options& Store::option(int index)
{
    return options.at(index); // can't figure out why this breaks
}

int Store::new_desktop()
{
    Desktop newest{};
    desktops.push_back(d);
    return desktops.size()-1;
}

void Store::add_desktop(int desktop, int order)
{
    //brainfart
}

int Store::num_orders()
{
    return orders.size();
}

Order& Store::order(int index)
{
    return orders.at(index);
}
