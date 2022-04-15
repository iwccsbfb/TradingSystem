#pragma once
#include <string>
#include <iostream>
#include <set>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include "order.h"
/*
A few ways to design orderBook:
1. only save prices; unordered_map that maps price to a OrderQueue;
    Then how to design the queue? use list or deque
2. lasy handling; Keep inserting all the delete values to another priority_queue.
    When you are popping values from the original priority queue, check with top
    of del_pq and see if we wanted to delete it. If it matches, delete the value from the original priority_queue.
    Can take up twice the memory, but average delete and inserts remain O(logN).
    del_pq could grow very big - then how to delete elements from del_pq?
4. one priority_queue (heap);
    delete: O(N) to find an element;
3. use set (binary search tree):
    std::set<int> pq;
    //accessing the smallest element(use as min heap)
    *pq.begin();
    //accessing the largest element (use as max heap)
    *pq.rbegin();
    //to delete the integer '6'
    auto it = pq.find(6);
    pq.erase(it);
*/

// store Order or Order*
class OrderBook {
public:
    OrderBook(OrderSide side): side(side) {}

    // insert: O(logN)
    void insert(const Order& order) {
        assert(order.side == side);
        orders.insert(order);
    }


    // remove certain element in a set: log(N)
    void remove(int64_t order_id) {
        // erase from both map and set
        auto o = Order();
        o.order_id = order_id;
        // auto it = orders.find(order_id, );
        // TODO: set.find is faster than std::find, but set.find cannot use customized == operator
        auto it = std::find(orders.begin(), orders.end(), o);
        orders.erase(it);
    }

    void print() {
        cout << side << endl;
        for (auto o : orders)
            cout << '\t' << o.order_id << ' ' << o.time << ' ' 
            << o.price.to_str() << ' ' << o.quantity << endl;
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

private:
    set<Order> orders;
    OrderSide side;
};
