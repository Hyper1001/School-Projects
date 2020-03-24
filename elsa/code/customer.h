#ifndef __CUSTOMER_H
#define __CUSTOMER_H
#include <string>
#include <iostream>
class Customer
{
private:
    std::string _name;
    std::string _phone;
    std::string _email;
public:
    Customer(std::string name,std::string phone, std::string email);
    friend std::ostream& operator<<(std::ostream& ost, const Customer& customer);
};
#endif
