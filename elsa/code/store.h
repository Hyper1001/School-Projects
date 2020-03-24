#ifndef __STORE_H
#define __STORE_H
#include "customer.h"
#include "options.h"
#include "desktop.h"
#include "order.h"
#include <iostream>
#include <vector>
#include <string>
class Store
{
private:
    std::vector<Customer> _customers;
    std::vector<Options*> _options;
    std::vector<Desktop> desktops;
    std::vector<Order> _orders;
public:
    void add_customer(Customer& customer)
    int num_customers();
    Customer& customer(int index);
    void add_option(Option& option);
    int num_options();
    Options& options(int index);
    int new_desktop();
    void add_option(int option, int desktop);
    int num_desktops();
    Desktop& desktop(int index);
    int new_order(int customer);
    void add_desktop(int desktop, int order);
    int num_orders();
    Order& order(int index);
};
#endif
