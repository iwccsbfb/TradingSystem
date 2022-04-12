
# include <string>
using namespace std;

class Order {
    public:
        string timestamp;
        unsigned time;
        unsigned client;
        bool buy;
        unsigned size;
        bool market;
        float price;
        
        Order(
                string timestamp, unsigned client, bool buy,
                unsigned size, bool market, float price): 
            timestamp(timestamp), time(to_time(timestamp)), client(client), buy(buy),
            size(size), market(market), price(price) {}
            
        Order(float price): time(UINT_MAX), price(price) {}
};

auto cmp = [](Order a, Order b) {
    if (a.buy) {
        // Buys should be ordered high->low for prospective sellers
        if (a.price != b.price) {
            return a.price > b.price;
        } else {
            return a.time < b.time;
        }
    } else {
        // Sells should be ordered low->high for prospective buyers
        if (a.price != b.price) {
            return a.price < b.price;
        } else {
            return a.time < b.time;
        }
    }
};



/*
auto cmp = [](Order a, Order b) {
    if (a.side = Order::OrderSide::BUY) {
        // Buys should be ordered high->low for prospective sellers
        if (a.price != b.price) {
            return a.price > b.price;
        }
        else {
            return a.time < b.time;
        }
    }
    else {
        // Sells should be ordered low->high for prospective buyers
        if (a.price != b.price) {
            return a.price < b.price;
        }
        else {
            return a.time < b.time;
        }
    }
};*/



void solve() {
    int n;
    string line;
    cin >> n;
    getline(cin, line);
    
    // Order books
    set<Order, decltype(cmp)> buys(cmp);
    set<Order, decltype(cmp)> sells(cmp);
}








