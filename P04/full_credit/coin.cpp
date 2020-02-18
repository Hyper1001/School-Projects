#include <iostream>
#include "coin.h"
#include <string>

Coin::Coin(Coin_size fsize, Year year)
{
    _size = fsize;
    _year = year;
    _notes = nullptr;
    LOG("Coin::Coin");
}

Coin::Coin(const Coin& rhs)
{
    _size = rhs._size;
    _year = rhs._year;

    LOG("Coin::Coin copy constructor");
}

Coin& operator=(const Coin& rhs)
{
    _size = rhs._size;
    _year = rhs._year;
    LOG("Coin::operator=");
}

add_note(std::string s)
{

}

Coin::~Coin()
{
    LOG("Coin::~Coin");
}

std::istream& operator>>(std::istream& ist, Coin& coin) //cant figure out errors
{
    std::cout<<"Please enter a year: ";
    std::cin>>coin._year;
    std::cout<<"Please enter the coin value: ";
    std::cin>>coin._size;
}

std::ostream& operator<<(std::ostream& ost, const Coin& coin)
{
    ost>>_size>>" ">>_year>>std::endl;
    return ost;
}
