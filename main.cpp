

/*
TODO: install boost library; json library;
    check boost set find: https://www.boost.org/doc/libs/1_43_0/doc/html/intrusive/advanced_lookups_insertions.html
    boost::intrusive::set find
    static polymorphism;

    void * + dynamic_cast or reinterpret_cast ?
    template: std::enable_if, std::conditional

    https://www.szse.cn/aboutus/research/secuities/documents/t20040106_531488.html

Matching Engine:

publisher:

std::variant; std::conditional_if
*/

// #include "order_book.h"
#include "price.h"
#include "order.h"

#include <boost/intrusive/set.hpp>
#include <boost/container/set.hpp>
#include <iostream>
#include <algorithm>

struct delete_disposer
{
    void operator()(Order *delete_this)
    {
        delete delete_this;
    }
};

struct OrderIdEqual
{
    bool operator()(const int num, const Order &o) const
    {
        return num == o.order_id;
    }

    bool operator()(const Order &o, const int num) const
    {
        return num == o.order_id;
    }
};

int main()
{
    auto p1 = Price4("12.23245"), p2 = Price4("20.23245");
    p1 = p2;
    std::cout << p1.to_str() << std::endl;

    boost::intrusive::set<Order> s;

    // auto buy_book = OrderBook(OrderSide::BUY), sell_book = OrderBook(OrderSide::SELL);
    Order orders[] = {
        Order(2, "AAPL", OrderSide::BUY, OrderType::LIMIT, Price4("12.3"), 200, 10005),
        Order(1, "AAPL", OrderSide::BUY, OrderType::LIMIT, Price4("12.23245"), 100, 10000),
        Order(3, "GOOG", OrderSide::BUY, OrderType::LIMIT, Price4("120"), 300, 10002),
        Order(4, "AAPL", OrderSide::BUY, OrderType::LIMIT, Price4("12.3"), 200, 10000),
        Order(5, "AAPL", OrderSide::BUY, OrderType::LIMIT, Price4("12.3"), 200, 10001)};
    for (int i = 0; i < sizeof(orders) / sizeof(Order); i++)
        s.insert(orders[i]);
    auto dummy = Order();
    dummy.order_id = 1;

    auto temp = s.find(1, OrderIdEqual());
    if (temp != s.end())
    {
        std::cout << temp->order_id << std::endl;
        // s.erase(dummy);
    }
    for (auto it : s)
        std::cout << it.order_id << std::endl;
    // //     // for (int i=0; i<sizeof(orders) / sizeof(Order); i++)
    // //     //     buy_book.insert(orders[i]);
    // //     // buy_book.print();
    // //     // buy_book.remove(2);
    // //     // buy_book.print();
    return 0;
}
