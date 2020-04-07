#include "customer.h"

Customer::Customer(std::string name, std::string phone, std::string email)
    : _name{name}, _phone{phone}, _email{email} {}
std::ostream& operator<<(std::ostream& ost, const Customer& customer) {
    ost << customer._name << " (" << customer._phone << "," << customer._email << ")";
    return ost;
}

Customer::Customer(std::istream& ist)
    :_name{}, _phone{}, _email{}
{
    ist >> _name;
    ist >> _phone;
    ist >> _email;
    ist.ignore(32767, '\n');
}

void Customer::save(std::ostream& ost)
{
    ost << _name <<" "<<_phone<<" "<<_email << std::endl;
}
