#include "Quote.hpp"
#include "Bulk_quote.hpp"
#include "Basket.hpp"
#include <vector>
#include <memory>

void exc_15_6()
{
    std::cout << "Exercise 15.6" << std::endl;
    Quote a("H-001", 1);
    Bulk_quote b("H-002", 2, 4, 0.2);
    print_total(std::cout, a, 2);
    print_total(std::cout, b, 2);
    print_total(std::cout, b, 5);
}

void exc_15_15()
{ 
    std::cout << "Exercise 15.15" << std::endl;
    Quote a("H-001", 1);
    Bulk_quote b("H-002", 2, 4, 0.2);
}

void exc_15_26()
{
    std::cout << "Exercise 15.26" << std::endl;
    Bulk_quote a("H-002", 2, 4, 0.2), c;
    std::cout << "-----------\n";
    Bulk_quote b(a);
    std::cout << "-----------\n";
    c = a;
    std::cout << "-----------\n";
    
}

void exc_15_28()
{
    std::cout << "Exercise 15.28" << std::endl;
    std::vector<std::shared_ptr<Quote>> vector;

    vector.push_back(std::shared_ptr<Quote>(new Quote("H-001", 2)));
    vector.push_back(std::shared_ptr<Quote>(std::move(new Bulk_quote("H-002", 2, 0, 0.2))));

    for (auto item : vector)
    {
        std::cout << "Price: "<<item->net_price(5) << std::endl;
    }

}

void exc_15_30()
{
    std::cout << "Exercise 15.30" << std::endl;
    Basket bsk;
    Quote a("H-001", 2);
    Bulk_quote b("H-002", 2, 1, 0.2);
    Bulk_quote c = b;
    // bsk.add_item(a);
    bsk.add_item(b);
    bsk.total_receipt(std::cout);
}


int main(int argc, char const *argv[])
{
    // exc_15_6();
    // exc_15_15();
    // exc_15_26();
    // exc_15_28();
    exc_15_30();
    return 0;
}
