#ifndef __DESKTOP_H
#define __DESKTOP_H

#include "options.h"
#include <vector>
#include <fstream>
class Desktop {
  public:
    void add_option(Options& option);
    double price();
    friend std::ostream& operator<<(std::ostream& ost, const Desktop& desktop);
    Desktop();
    Desktop(std::istream& ist);
    void save(std::ostream& ost);
  private:
    std::vector<Options*> options;
};

#endif
