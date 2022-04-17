#ifndef PRICE_H
#define PRICE_H


//#pragma once
#include <string>
#include <iostream>

class Price4 {
public:
    Price4() = default;
    explicit Price4(long unscaled) : unscaled_(unscaled) {}

    // convert from string
    explicit Price4(const std::string& s) {
        std::string target = s;
        int idx = s.find_first_of('.');
        int len = 0; // length of after .
        if (idx != std::string::npos) {
            std::string p1 = s.substr(0, idx), p2 = s.substr(idx + 1, 4);
            target = p1 + p2;
            len = p2.size();
        }
        unscaled_ = stoi(target);
        for (; len < 4; len++)
            unscaled_ *= 10;
    }

    long unscaled() const { return unscaled_; }

    // convert to string
    std::string to_str() const {
        return std::to_string(unscaled_ / 10000) + "." +
            std::to_string(unscaled_ % 10000);
    }

    bool operator < (const Price4& other) const {
        return unscaled_ < other.unscaled_;
    }

    bool operator > (const Price4& other) const {
        return unscaled_ > other.unscaled_;
    }

    bool operator == (const Price4& other) const {
        return unscaled_ == other.unscaled_;
    }

    bool operator != (const Price4& other) const {
        return unscaled_ != other.unscaled_;
    }

    Price4 & operator = (const Price4& other) {
        unscaled_ = other.unscaled_;
        return *this;
    }

private:
    long unscaled_;
};

std::ostream & operator<<(std::ostream& os, Price4 const& m) {
    return os << m.to_str();
}



#endif