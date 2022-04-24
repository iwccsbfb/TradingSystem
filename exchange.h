#ifndef EXCHANGE_H
#define EXCHANGE_H
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <nlohmann/json.hpp>
#include "price.h"
#include "order.h"
#include "order_book.h"

class Config {
    std::set<std::string> symbols;
    std::map<Price4, Price4> tick_map; // map lower bound price to tick_size price
public:
    Config() = delete;
    Config(std::string path) {
        std::ifstream in(path);
        std::ostringstream sstr;
        sstr << in.rdbuf();
        std::string s = sstr.str();
        nlohmann::json j = nlohmann::json::parse(s);
        for(auto &s: j["symbols"])
            symbols.insert(s);
        for(auto &t: j["tick_rules"]) {
            Price4 p1 = Price4(std::string(t["from_price"])), 
                p2 = Price4(std::string(t["tick_size"]));
            tick_map[p1] = p2;
        }            
    }

    // validate if a price meets the tick_size requirement
    bool validate_price(const Price4 &p) {
        auto it = tick_map.upper_bound(p);
        if (it == tick_map.begin()) return false;
        --it;
        Price4 tick_size = it->second;
        // TODO: test
        return p.unscaled() % tick_size.unscaled() == 0;
    }

    bool validate_symbol(const std::string & symbol) {
        return symbols.find(symbol) != symbols.end();
    }
};


// this is a singleton class
class Exchange {
public:
    static Exchange* get_instance() {
        if(instance == nullptr) {
            instance = new Exchange();
        }
        return instance;
    }
    Exchange(Exchange &) = delete;
    void operator=(const Exchange &) = delete;

    void insert_order(const Order &order) {
        symbol_map[order.order_id] = order.symbol;
        if(ob_map.find(order.symbol) == ob_map.end() )
            ob_map[order.symbol] = new OrderBook();
        ob_map[order.symbol]->insert(order); // TODO: trade matching
    }

    void remove_order(const int64_t && order_id) {
        std::string symbol = symbol_map[order_id];
        ob_map[symbol]->remove(order_id);
    }
    
    ~Exchange() {
        for(auto &p: ob_map) // delete all OrderBook objects
            delete p.second;
    }
private:
    Exchange() {
    }
    // since c++ 17, inline static can be initialized within class. O/W, it needs to be initialized outside
    inline static Exchange * instance = nullptr;
    std::map <int64_t, std::string> symbol_map; // map order_id to symbol
    std::map <std::string, OrderBook*> ob_map;  // map symbol to its orderBook
};







#endif

