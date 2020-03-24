#include "desktop.h"
#include <vector>
#include <iostream>

void Desktop::add_option(Options& option)
{
    options.push_back(&option);
}

double Desktop::price()
{
    double total = 0;
    for(int i =0;i<options.size();i++)
    {
        total+=options[i]->cost();
    }
    return total;
}

std::ostream& operator<<(std::ostream& ost, const Desktop& desktop)
{
    ost << "Desktop priced at $"<< desktop.price();
    return ost;
}
