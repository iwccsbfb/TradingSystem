#ifndef EXCHANGE_H
#define EXCHANGE_H
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <nlohmann/json.hpp>
#include "price.h"

class Exchange {
    std::set<std::string> symbols;
    std::map<Price4, Price4> tick_map; // map lower bound price to tick_size price
public:
    void load_config(std::string path) {
        std::ifstream in("data/config.json");
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










#endif

