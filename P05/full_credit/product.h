#ifndef __PRODUCT_H
#define __PRODUCT_H
#include <string>

class Product
{
protected:
    int _quantity;
    double _cost;
    std::string _name;
public:
    Product(std::string name, double cost);
    virtual ~Product();
    friend std::ostream& operator<<(std::ostream& ost, const Product& product);
    void set_quantity(int quantity);
    virtual const double price()=0;
};

#endif // __PRODUCT_H
