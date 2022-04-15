#include "order_book.h"
#include "price.h"
#include "order.h"

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



using namespace std;


int main() {
    auto p1 = Price4("12.23245"), p2 = Price4("20.23245");
    p1 = p2;
    cout << p1.to_str() << endl;

    auto buy_book = OrderBook(OrderSide::BUY), sell_book = OrderBook(OrderSide::SELL);
    Order orders[] = {
        Order(2, "AAPL", OrderSide::BUY, OrderType::LIMIT, Price4("12.3"), 200, 10005),
        Order(1, "AAPL", OrderSide::BUY, OrderType::LIMIT, Price4("12.23245"), 100, 10000),
        Order(3, "GOOG", OrderSide::BUY, OrderType::LIMIT, Price4("120"), 300, 10002),
        Order(4, "AAPL", OrderSide::BUY, OrderType::LIMIT, Price4("12.3"), 200, 10000),
        Order(5, "AAPL", OrderSide::BUY, OrderType::LIMIT, Price4("12.3"), 200, 10001)
    };
    for (int i=0; i<sizeof(orders) / sizeof(Order); i++)
        buy_book.insert(orders[i]);
    buy_book.print();
    buy_book.remove(2);
    buy_book.print();
	return 0;
}

