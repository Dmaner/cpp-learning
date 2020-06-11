#ifndef BASKET_H
#define BASKET_H

#include "Quote.hpp"
#include "Bulk_quote.hpp"
#include <set>
#include <memory>

class Basket
{
public:
    void add_item(std::shared_ptr<Quote> &sale)
    {
        set.insert(sale);
    }
    void add_item(const Quote &sale)
    {
        set.insert(std::shared_ptr<Quote>(sale.clone()));
    }
    void add_item(Quote &&sale)
    {
        set.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }
    double total_receipt(std::ostream &os) const
    {
        double ans = 0.0;
        for (auto iter = set.cbegin(); iter != set.cend(); iter = set.upper_bound(*iter))
        {
            ans += print_total(os, **iter, set.count(*iter));
        }
        os << "Total sale: " << ans << std::endl;
        return ans;
    }

private:
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs)
    {
        return lhs->isbn() < rhs->isbn();
    }
    std::multiset<std::shared_ptr<Quote>, decltype(compare) *> set{compare};
};

#endif