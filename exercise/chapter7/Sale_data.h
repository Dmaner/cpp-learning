#ifndef SALE_DATA_H
#define SALE_DATA_H

#include <iostream>
#include <string>
using std::cin; 
using std::cout; 
using std::endl; 
using std::string;

class Sales_data
{
    friend Sales_data add(Sales_data&, Sales_data&);
    friend std::istream& read(std::istream&, Sales_data&);
    friend std::ostream& print(std::ostream&, const Sales_data&);
public:
    Sales_data() = default;
    Sales_data(const string &s): bookNo(s) {};
    Sales_data(const string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(n*p) {};
    Sales_data(std::istream &);
    
	std::string const& isbn() const { return bookNo; };
    inline double avg_price() const {return units_sold ? revenue/units_sold : 0;};
	Sales_data& combine(const Sales_data&);
private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data& Sales_data::combine(const Sales_data& rhs){
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

std::istream& read(std::istream &is, Sales_data &item){
	double price = 0.0;
	is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream& print(std::ostream& os, const Sales_data& item){
    os << item.bookNo << " " << item.units_sold << " "<< item.revenue;
    return os;
}

Sales_data add(Sales_data &a, Sales_data &b){
    Sales_data result = a;
    result.combine(b);
    return result;
}

Sales_data::Sales_data(std::istream &is){
    read(is, *this);
}

#endif