#ifndef __TAXFREE_H
#define __TAXFREE_H
#include <string>
#include "product.h"
class Taxfree : public Product
{

public:
    Taxfree(std::string name,double cost);
    virtual ~Taxfree();
    const double price();
};
#endif __TAXFREE_H
