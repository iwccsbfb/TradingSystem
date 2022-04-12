
// #include r"D:\dev\projects\vcpkg\packages\jsoncpp_x86-windows\include\json\json.h"

// "-DCMAKE_TOOLCHAIN_FILE=D:/dev/projects/vcpkg/scripts/buildsystems/vcpkg.cmake"


//The package jsoncpp provides CMake targets :

//find_package(jsoncpp CONFIG REQUIRED)
//target_link_libraries(main PRIVATE jsoncpp_lib jsoncpp_object JsonCpp::JsonCpp)
#include "order_book.h"
#include "price.h"
#include "order.h"

using namespace std;


int main() {
    auto p1 = Price4("12.23245"), p2 = Price4("20.23245");
    p1 = p2;
    cout << p1.to_str() << endl;

    auto buy_book = OrderBook(OrderSide::BUY), sell_book = OrderBook(OrderSide::SELL);
    Order orders[] = {
        Order(2, "AAPL", OrderSide::BUY, Price4("12.3"), 200, 10005),
        Order(1, "AAPL", OrderSide::BUY, Price4("12.23245"), 100, 10000),
        Order(3, "GOOG", OrderSide::BUY, Price4("120"), 300, 10002),
        Order(4, "AAPL", OrderSide::BUY, Price4("12.3"), 200, 10000),
        Order(5, "AAPL", OrderSide::BUY, Price4("12.3"), 200, 10001)
    };
    for (int i=0; i<sizeof(orders) / sizeof(Order); i++)
        buy_book.insert(orders[i]);
    buy_book.print();
    buy_book.remove(2);
    buy_book.print();
	return 0;
}

