#ifndef ORDER_H
#define ORDER_H

#include "price.h"
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/unordered_set.hpp>


#include <string>

class Price4;
static int64_t max_order_id = 0;
enum OrderSide { BUY, SELL };
enum OrderType { MARKET, LIMIT, ICEBERG};

const int ICEBERG_DISPLAY_QUANTITY = 100;


class Order : public boost::intrusive::set_base_hook<>, public boost::intrusive::unordered_set_base_hook<> {
public:

    int64_t order_id;
    std::string symbol;
    OrderSide side;
    OrderType order_type;
    Price4 price;
    int64_t quantity;
    int64_t time;
    int64_t hidden_quantity = 0; // TODO: where to set this as 0

    Order() = default;
    Order(int64_t order_id, std::string symbol, OrderSide side, OrderType order_type, Price4 price, int64_t quantity, int64_t time) 
        : order_id(order_id), symbol(symbol), side(side), order_type(order_type), price(price), quantity(quantity), time(time)
    {
        if(order_type == OrderType::ICEBERG && quantity > ICEBERG_DISPLAY_QUANTITY) {
            hidden_quantity = quantity - ICEBERG_DISPLAY_QUANTITY;
            quantity = ICEBERG_DISPLAY_QUANTITY;
        }
    }

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

    void done() { // when an order is processed
        if (order_type == OrderType::ICEBERG && hidden_quantity > ICEBERG_DISPLAY_QUANTITY) {
            hidden_quantity = quantity - ICEBERG_DISPLAY_QUANTITY;
            quantity = ICEBERG_DISPLAY_QUANTITY;
        }
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


class IcebergOrder : public Order {
    IcebergOrder() {}
};



#endif