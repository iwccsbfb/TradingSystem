# CMakeList.txt : CMake project for tradingSystem-cmake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (tradingSystem-cmake "main.cpp"  "order.cpp" "order.h" "price.h" "order_book.h" "matching_engine.h")

# TODO: Add tests and install targets if needed.
