#ifndef __TAXED_H
#define __TAXED_H
#include <string>
#include "product.h"
class Taxed: public Product
{
private:
    static double tax;
public:
    Taxed(std::string name,double cost);
    virtual ~Taxed();
    static void set_tax_rate(double sales_tax)
    const double price();
};
#endif // __TAXED_H
