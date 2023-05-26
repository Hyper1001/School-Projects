#include "cart.h"
#include "item.h"
#include <iostream>
#include <iomanip>

int main()
{
    Cart cart{"placeholder name"};
    Item item{"itemname",0};
    std::cout<<"Enter product names and prices (e.g, \"English peas 0.79\""<<endl;
    //Should take user inputs as items and push them back onto cart if they are have no errors. If there is an error, output the error message.
    std::cout<<"Register Receipt\n"<<endl;
    //Print out all items with the istream operator we set up.
    std::cout<<"--------------------------------------------------------------------------"<<std::endl;
    std::cout<<std::fixed<<std::setprecision(2)<<"$\t"<<cart.cost()<<"\tTotalCost"<<std::endl;
}
