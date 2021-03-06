// #pragma once
#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "order.h"
#include <string>
#include <iostream>
#include <set>
#include <unordered_map>
#include <nlohmann/json.hpp>
/*
A few ways to design orderBook:
1. First level data structure is a deque of prices; 
    Then how to design the queue? use list or deque
2. lasy handling; Keep inserting all the delete values to another priority_queue.
    When you are popping values from the original priority queue, check with top
    of del_pq and see if we wanted to delete it. If it matches, delete the value from the original priority_queue.
    Can take up twice the memory, but average delete and inserts remain O(logN).
    del_pq could grow very big - then how to delete elements from del_pq?
4. one priority_queue (heap);
    doesn't work for delete: It takes O(N) to find an element;
3. use set (binary search tree);
    By default, bst is sorted by order preference - not by order_id. 
    Therefore when we do find by order_id, we need to have a map to get this order object, thus to achieve O(LogN) .
*/


class OrderBook {
public:
    OrderBook() = default;

    void insert(const Order& order) { 
        Order no(order); // new order
        std::set<Order> &match_orders = (order.side == OrderSide::SELL) ? buy_orders : sell_orders;
        // for(auto it = buy_orders.begin(); it != buy_orders.end() && order.price <= it->price; it++) {
        while(!match_orders.empty()) {
            auto node = match_orders.extract(match_orders.begin());
            Order &o = node.value();
            if( (no.side == OrderSide::SELL && no.price > o.price) || 
                (no.side == OrderSide::BUY && no.price < o.price))
                break;
            if(o.quantity >= no.quantity) { // match new-order completely
                o.quantity -= no.quantity;
                no.quantity = 0;
                // TODO: print matching information
            }
            else { // match old order completely
                no.quantity -= o.quantity;
                o.quantity = 0;
            }
            if (o.quantity == 0)
                o.done(); // handle ICEBERG order
            if (o.quantity != 0)
                match_orders.insert(std::move(node));
            if(no.quantity == 0)
                break;
        }
        if(no.quantity != 0) {
            // insert: O(logN)
            std::set<Order> &orders = (order.side == OrderSide::BUY) ? buy_orders : sell_orders;
            orders.insert(no);
            m[order.order_id] = &no;
        }
    }

    // remove certain element in a set: log(N)
    void remove(const int64_t order_id) {
        // erase from both map and set
        const Order* o = m[order_id];
        m.erase(order_id);

        std::set<Order> &orders = (o->side == OrderSide::BUY) ? buy_orders : sell_orders;
        auto it = orders.find(*o);
        orders.erase(it);
    }

    void print() {
        std::cout << "BID:" << std::endl;
        for (auto o : buy_orders)
            std::cout << '\t' << o.order_id << ' ' << o.quantity << ' ' << o.price.to_str() << ' ' 
             << o.time << ' ' << std::endl;

        std::cout << "ASK:" << std::endl;
        for (auto o : sell_orders) {
            std::cout << '\t' << o.price.to_str() << ' '  << o.quantity << ' ' << o.order_id << ' '
             << o.time << ' ' << std::endl;
            // std::cout << '\t' << o.order_id << ' ' << o.quantity << ' ' << o.price.to_str() << ' ' 
            //  << o.time << ' ' << std::endl;
        }
    }

    /*
    void aggregate_by_price() {
        bool start = true;
        Price4 prev;
        for (auto o : s) {
            if (start) { 
                start = false;
                prev = o.price;
                continue;
            }

        }
    }*/

    nlohmann::json to_json() {
        // dump GTC orders at the end of day
        nlohmann::json j;
        for(auto o: buy_orders) {
            if (o.tif == TimeInForce::GTC) {

            }
        }
        return j;
    }

private:
    std::set<Order> buy_orders, sell_orders;
    std::unordered_map<int64_t, const Order*> m; // map order id to Order
};


#endif