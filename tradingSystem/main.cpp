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


auto cmp = [](Order a, Order b) {
    if (a.buy) {
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




int main() {
	cout << 123 << endl;
	return 0;
}