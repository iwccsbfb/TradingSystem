#include <string>
#include <iostream>
using namespace std;

enum OrderSide {BUY, SELL};

class Order {
public:
	int64_t order_id; 
	string symbol; 
	OrderSide side;
	float price;
	int64_t quantity;
    int64_t time;
};


class Price4 {
public:
    Price4(string s) {
        int idx = s.find_first_of('.');
        if (idx != string::npos)
            s = s.substr(0, idx) + s.substr(idx + 1, 4);
        price = stoi(s);
    }
    Price4(float p) {
        price = int(p * 10000);
    }

private:
    int64_t price; // denote int(real_price*10000)
};


auto cmp = [](Order a, Order b) {
    if (a.side = OrderSide::BUY) {
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
};
// price4 & Orderbook



int main() {
	cout << 123 << endl;
	return 0;
}