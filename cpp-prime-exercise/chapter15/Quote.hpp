#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <string>

class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}

    // define !=
    bool inline operator!=(const Quote &rhs)
    {
        return rhs.price != price || rhs.bookNo != bookNo;
    }

    // copy constructor
    Quote(const Quote &rhs)
    {
        // std::cout << "Quote copying constructor\n";
        bookNo = rhs.bookNo;
        price = rhs.price;
    }

    Quote &operator=(const Quote &rhs)
    {
        if (*this != rhs)
        {
            bookNo = rhs.bookNo;
            price = rhs.price;
        }
        // std::cout << "Quote: copy =() \n";

        return *this;
    }

    // move constructor
    Quote(Quote &&rhs) noexcept : bookNo(std::move(rhs.bookNo)), price(std::move(rhs.price))
    {
        // std::cout << "Quote move constructor\n";
    }

    Quote &operator=(Quote &&rhs) noexcept
    {
        if (*this != rhs)
        {
            bookNo = std::move(bookNo);
            price = std::move(price);
        }
        std::cout << "Quote move =()\n";
        return *this;
    }

    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual void debug() const { std::cout << "Book No: " << bookNo << " Price: " << price << std::endl; }
    virtual ~Quote()
    {
        // std::cout << "Quote destructor\n";
    }

    // exercise 15.30
    virtual Quote *clone() const &
    {
        std::cout << "Quote clone !\n";
        return new Quote(*this);
    }
    virtual Quote *clone() &&
    {
        std::cout << "Quote move clone !\n";
        return new Quote(std::move(*this));
    }

private:
    std::string bookNo;

protected:
    double price = 0.0;
};

class Disc_quote : public Quote
{
public:
    Disc_quote();
    Disc_quote(const std::string &s, double p, size_t qty, double disc) : Quote(s, p), min_qty(qty), discount(disc) {}

    // copy function
    Disc_quote(const Disc_quote &rhs) : Quote(rhs) {}
    Disc_quote(Disc_quote &&rhs) noexcept : Quote(std::move(rhs)) {}
    Disc_quote &operator=(const Disc_quote &rhs)
    {
        Quote::operator=(rhs);
        return *this;
    }
    Disc_quote &operator!=(Disc_quote &&rhs) noexcept
    {
        Quote::operator=(std::move(rhs));
        return *this;
    }

    double net_price(size_t) const = 0;

protected:
    size_t min_qty = 0;
    double discount = 0.0;
};

double print_total(std::ostream &os, Quote &item, size_t n)
{
    double ans = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ans << std::endl;
    return ans;
}

#endif