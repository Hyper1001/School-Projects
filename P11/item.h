#ifndef __ITEM_H
#def __ITEM_H

class Item
{
    public:
        Item(std::string name,double price);
        double cost();
        friend std::ostream& operator<<(std::ostream& ost, cosnt Item& item);
        friend std::istream& operator>>(std::istream& ist, Item& item);
    private:
        std::string _name;
        double _price;
}
#endif // __ITEM_H
