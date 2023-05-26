#include "options.h"

Options::Options(std::string name, double cost) : _name{name}, _cost{cost} {}
Options::~Options() {}
double Options::cost() {return _cost;}
std::string Options::to_string() const {
    return _name + " ($" + std::to_string(_cost) + ")";
}
std::ostream& operator<<(std::ostream& ost, const Options& options) {
    // ost << options.to_string();
    ost << options._name << " ($" << options._cost << ")";
    return ost;
}

Options::Options(std::istream& ist)
    : _name{}, _cost{}
{
    std::getline(ist,_name);
    ist>>_cost;
    ist.ignore(32767, '\n');
}

void Options::save(std::ostream& ost)
{
    ost<<_name<<endl;
    ost<<_cost<<endl;
}
