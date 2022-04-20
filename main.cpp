

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


https://towardsdatascience.com/how-to-build-a-multi-threaded-pipeline-in-c-with-std-async-78edc19e862d
static cannot virtual; 


standard testing case:


*/

#include "price.h"
#include "order.h"
#include "order_book.h"
#include "exchange.h"

#include <nlohmann/json.hpp>
#include <fstream>

int main()
{
    // auto j3 = nlohmann::json::parse(R"({"happy": true, "pi": 3.141})");
    // nlohmann::json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
    // j["sub"] = j3;
    // std::string s = j.dump();

    std::ifstream infile("data/input.jsonl");
    std::string line;
    while (std::getline(infile, line))
    {
        // std::cout << line << std::endl;
        auto j = nlohmann::json::parse(line);
        int64_t time = j["time"], order_id = j["order_id"];
        if(j["type"] == std::string("NEW")) {
            std::string symbol = j["symbol"];
            OrderSide side = OrderSideConverter::from_string(j["side"]);
            int quantity = j["quantity"];
            auto price = Price4(std::string(j["limit_price"])); 
            auto order = Order(order_id, symbol, side, OrderType::LIMIT, TimeInForce::DAY, price, quantity, time);
        }else if(j["type"] == std::string("CANCEL")) {

        }
    }

    auto book = OrderBook();
    Order orders[] = {
        Order(2, "AAPL", OrderSide::BUY, OrderType::LIMIT, TimeInForce::DAY, Price4("12.3"), 200, 10005),
        Order(1, "AAPL", OrderSide::BUY, OrderType::LIMIT, TimeInForce::DAY, Price4("12.23245"), 100, 10000),
        Order(3, "GOOG", OrderSide::BUY, OrderType::LIMIT, TimeInForce::GTC, Price4("120"), 300, 10002),
        Order(4, "AAPL", OrderSide::BUY, OrderType::LIMIT, TimeInForce::DAY, Price4("12.3"), 200, 10000),
        Order(5, "AAPL", OrderSide::BUY, OrderType::LIMIT, TimeInForce::GTC, Price4("12.3"), 200, 10001)};
    for (int i = 0; i < sizeof(orders) / sizeof(Order); i++)
        book.insert(orders[i]);

    book.print();
    book.remove(2);
    book.print();
    return 0;
}
