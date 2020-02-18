#ifndef __COIN_H
#define __COIN_H
#include <string>
#include "logger.h"

typedef int Year;
enum class Coin_size{PENNY = 1; NICKEL = 5, DIME = 10; QUARTER =25};

class Coin
{
private:
    typedef int Year _year;
    std::string* _notes;
    Coin_size = _size;
public:
    Coin(Coin_size fsize, Year year);
    Coin(const Coin& rhs)
    Coin& operator=(const Coin& rhs)
    ~Coin();
    add_note(std::string s);
    friend std::ostream& operator<<(std::ostream& ost, const Coin& coin);
    friend std::istream& operator>> (std::istream ist, Coin& coin);
};

#endif
