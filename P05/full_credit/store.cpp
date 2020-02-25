#include <iostream>
#include <vector>
#include "product.h"
#include "taxed.h"
#include "taxfree.h"

int main()
{
    int input = 10000000000000;
    Taxfree milk("Milk",2.85);
    Taxfree bread("Bread",1.99);
    Taxfree cheese("Cheese",0.99);
    Taxed icecream("Ice Cream",4.95);
    Taxed poptarts("Poptarts",3.49);
    Taxed oreos("Oreos",5.99);
    std::vector<Product> cart;
    while(input!=0)
    {
        std::cout<<"====================="<<
        std::endl<<"Welcome to the Store"<<
        std::endl<<"====================="<<
        std::endl<<"0) "<<milk<<
        std::endl<<"1) "<<bread<<
        std::endl<<"2) "<<cheese<<
        std::endl<<"3) "<<icecream<<
        std::endl<<"4) "<<poptarts<<
        std::endl<<"5) "<<Oreos<<std::endl<<
        std::endl<<"Enter the quantity (0 to exit) and product index: ";
        cin>>input;
        //add products to cart vector
        std::cout<<std::endl;
        if(cart.size()!=0)
        {
            std::cout<<Current Order<<
            std::endl<<"-------------"<<
            std::endl;// print out all items and their prices in cart by using <<.
        }
    }
}
