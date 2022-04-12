#pragma once
#include "price.h"


#include <string>
#include <iostream>
#include <set>
using namespace std;


class Price4;
static int64_t max_order_id = 0;
enum OrderSide { BUY, SELL };

class Order {
public:

    int64_t order_id;
    string symbol;
    OrderSide side;
    Price4 price;
    int64_t quantity;
    int64_t time;

    Order() = default;
    Order(int64_t order_id, string symbol, OrderSide side, Price4 price, int64_t quantity, int64_t time) 
        : order_id(order_id), symbol(symbol), side(side), price(price), quantity(quantity), time(time)
    {}

    bool operator < (const Order& other) const {
        // return true if current order is more favorable
        if (side == OrderSide::BUY) {
            // Buys should be ordered high->low for prospective sellers
            if (price != other.price) {
                return price > other.price;
            }
            else {
                return time < other.time;
            }
        }
        else {
            // Sells should be ordered low->high for prospective buyers
            if (price != other.price) {
                return price < other.price;
            }
            else {
                return time < other.time;
            }
        }
    }

    bool operator == (const Order& other) const {
        return order_id == other.order_id;
    }
};

template <>
struct std::hash<Order>
{
    std::size_t operator()(const Order& k) const
    {
        return hash<int64_t>()(k.order_id);
    }
};