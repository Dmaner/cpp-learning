#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H

#include "Quote.hpp"

class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote() = default;
    // exercise 15.27
    using Disc_quote::Disc_quote;

    // derived copy function from Quote
    Bulk_quote(const Bulk_quote &rhs) : Disc_quote(rhs)
    {
        std::cout << "Bulk quote copy constructor\n";
    }

    Bulk_quote(Bulk_quote &&rhs) noexcept : Disc_quote(std::move(rhs))
    {
        std::cout << "Bulk quote move constructor\n";
    }

    Bulk_quote &operator=(const Bulk_quote &rhs)
    {
        Disc_quote::operator=(rhs);
        std::cout << "Bulk quote copy =\n";
        return *this;
    }

    Bulk_quote &operator=(Bulk_quote &&rhs)
    {
        Disc_quote::operator=(rhs);
        std::cout << "Bulk quote move =\n";
        return *this;
    }
    ~Bulk_quote() override
    {
        std::cout << "Bulk quote destructor\n";
    }

    double net_price(std::size_t) const override;
    void debug() const override
    {
        std::cout << "Bulk quote debug message: \n";
        Disc_quote::debug();
        std::cout << "Discount: " << discount << " Min qty: " << min_qty << std::endl;
    }

    // exercise 15.30
    Bulk_quote *clone() const & override
    {
        std::cout << "Bulk quto clone!\n";
        this->debug();
        Bulk_quote *a = new Bulk_quote(*this);
        a->debug();
        return new Bulk_quote(*this);
    }
    Bulk_quote *clone() && override
    {
        std::cout << "Bulk quote move clone!\n";
        return new Bulk_quote(std::move(*this));
    }
};

double Bulk_quote::net_price(std::size_t n) const
{
    if (n >= min_qty)
        return n * (1 - discount) * price;
    else
        return n * price;
}

#endif