#ifndef ORDER_H
#define ORDER_H

#include "price.h"

#include <set>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

enum OrderSide
{
    BUY,
    SELL
};
const std::vector<std::string> orderSide_str = {"BUY", "SELL"};

enum OrderType
{
    MARKET,
    LIMIT,
    ICEBERG
};
const std::vector<std::string> orderType_str = {"MARKET", "LIMIT", "ICEBERG"};

enum TimeInForce
{
    DAY,
    IOC, // immediate or cancel
    GTC  // good till cancelled
};
const std::vector<std::string> timeInForce_str = {"DAY", "IOC", "GTC"};




template <class T, const std::vector<std::string> *values>
class EnumConverter {
    // static const std::vector<std::string> values() = 0;
public:
    static T from_string(std::string &&s) {
        for(int i=0; i<values->size(); i++) 
            if((*values)[i] == s)
                return T(i);
        throw std::string("wrong value!");
    }
    static std::string to_string(T &&v) {
        return (*values)[int(v)];
    }
};


class OrderSideConverter: public EnumConverter<OrderSide, &orderSide_str> {
};


class OrderTypeConverter: public EnumConverter<OrderType, &orderType_str> {
};


class TimeInForceConverter: public EnumConverter<TimeInForce, &timeInForce_str> {
};



const int ICEBERG_DISPLAY_QUANTITY = 100;

class Order
{
public:
    int64_t order_id;
    std::string symbol;
    OrderSide side;
    OrderType order_type;
    TimeInForce tif;
    Price4 price;
    int64_t quantity;
    int64_t time;
    int64_t hidden_quantity = 0; // TODO: where to set this as 0

    Order() = default;
    Order(int64_t order_id, std::string symbol, OrderSide side, OrderType order_type, TimeInForce tif, Price4 price, int64_t quantity, int64_t time)
        : order_id(order_id), symbol(symbol), side(side), order_type(order_type), tif(tif), price(price), quantity(quantity), time(time)
    {
        if (order_type == OrderType::ICEBERG && quantity > ICEBERG_DISPLAY_QUANTITY)
        {
            hidden_quantity = quantity - ICEBERG_DISPLAY_QUANTITY;
            quantity = ICEBERG_DISPLAY_QUANTITY;
        }
    }

    bool operator<(const Order &other) const
    {
        // return true if current order is more favorable
        if (side == OrderSide::BUY)
        {
            // Buys should be ordered high->low for prospective sellers
            if (price != other.price)
            {
                return price > other.price;
            }
            else
            {
                return time < other.time;
            }
        }
        else
        {
            // Sells should be ordered low->high for prospective buyers
            if (price != other.price)
            {
                return price < other.price;
            }
            else
            {
                return time < other.time;
            }
        }
    }

    // bool operator==(const Order &other) const
    // {
    //     return order_id == other.order_id;
    // }

    void done()
    { // when an order is fully matched
        if (order_type == OrderType::ICEBERG)
        {
            if (hidden_quantity > ICEBERG_DISPLAY_QUANTITY)
            {
                hidden_quantity -= ICEBERG_DISPLAY_QUANTITY;
                quantity = ICEBERG_DISPLAY_QUANTITY;
            }
            else
            {
                quantity = hidden_quantity;
                hidden_quantity = 0;
            }
            // TODO: change timestamp to current time;
        }
    }

    nlohmann::json to_json()
    {
        // TODO: used for nightly dump
        nlohmann::json j;
        std::cout << OrderSideConverter::to_string(OrderSide::BUY) << std::endl;
        std::cout << OrderTypeConverter::to_string(OrderType::ICEBERG) << std::endl;
        return j;
    }
};

// hash only based on order_id
template <>
struct std::hash<Order>
{
    std::size_t operator()(const Order &k) const
    {
        return hash<int64_t>()(k.order_id);
    }
};

class IcebergOrder : public Order
{
    IcebergOrder() {}
};

#endif