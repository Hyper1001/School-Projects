#include <iostream>
#include "coin.h"
#include <string>
#include "logger.h"

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
    this._notes = new std::string(*(rhs._notes));
    LOG("Coin::Coin copy constructor");
}

Coin& operator=(const Coin& rhs)
{
    _size = rhs._size;
    _year = rhs._year;
    this._notes = new std::string(*(rhs._notes));
    LOG("Coin::operator=");
    return *this;
}

std::string Coin::add_note(std::string s) //errors
{
    if(_notes==nullptr)
    {
        _notes = new std::string stringnew*;
        return stringnew = s;
    }
    return _notes +s;
}

Coin::~Coin()
{
    delete []_notes;
    LOG("Coin::~Coin");
}

std::istream& operator>>(std::istream& ist, Coin& coin) //errors
{
    std::cout<<"Please enter a year: ";
    std::cin>>coin._year;
    std::cout<<"Please enter the coin value: ";
    std::cin>>coin._size;
}

std::ostream& operator<<(std::ostream& ost, const Coin& coin)
{
    ost>>_size>>" ">>_year>>"\n";
    //INSERT CODE TO PRINT OUT _NOTES
    ost>>std::endl;
    return ost;
}
