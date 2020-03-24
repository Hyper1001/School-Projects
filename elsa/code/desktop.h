#ifndef __DESKTOP_H
#define __DESKTOP_H
#include "options.h"
#include <string>
#include <vector>
#include <iostream>
class Desktop
{
private:
    std::vector<Options*> options;
public:
    void add_option(Options& option)
    double price();
    friend std::ostream& operator<<(std::ostream& ost, const Desktop& desktop);
};
#endif
