#ifndef MONEY_H
#define MONEY_H

#include <cmath>
#include <ostream>
#include <string>
#include "core/Exceptions.h"
using namespace std;

// Fixed-point money: stored as an integer number of cents so balances never
// suffer floating-point drift (0.1 + 0.2 != 0.3 is not acceptable in a bank).
class Money {
private:
    long long cents;

public:
    Money() : cents(0) {}
    explicit Money(long long rawCents) : cents(rawCents) {}

    // Strict parser: "1500", "1500.5", "1500.75". No signs, no exponents.
    static Money fromString(const string& text) {
        size_t first = text.find_first_not_of(" \t");
        size_t last = text.find_last_not_of(" \t");
        if (first == string::npos) throw ValidationException("Amount is empty.");
        string s = text.substr(first, last - first + 1);

        size_t dot = s.find('.');
        string whole = (dot == string::npos) ? s : s.substr(0, dot);
        string frac = (dot == string::npos) ? "" : s.substr(dot + 1);

        bool bad = whole.empty() || whole.size() > 12 || frac.size() > 2;
        for (char c : whole) if (c < '0' || c > '9') bad = true;
        for (char c : frac) if (c < '0' || c > '9') bad = true;
        if (bad) throw ValidationException("Amount must look like 1500 or 1500.75 (max 2 decimals).");

        while (frac.size() < 2) frac += '0';
        return Money(stoll(whole) * 100 + stoll(frac));
    }

    // Return the raw value in cents (e.g., 1500.75 -> 150075)
    long long raw() const { return cents; }
    bool isPositive() const { return cents > 0; }
    bool isNegative() const { return cents < 0; }
    bool isZero() const { return cents == 0; }

    // Return a string representation (e.g., 1500.75 -> "1500.75")
    string toString() const {
        long long magnitude = cents < 0 ? -cents : cents;
        long long fraction = magnitude % 100;
        string result = to_string(magnitude / 100) + "." + (fraction < 10 ? "0" : "") + to_string(fraction);
        return cents < 0 ? "-" + result : result;
    }

    // Multiply by a rate (e.g. 0.04) and round to the nearest cent.
    Money scaled(double factor) const {
        return Money(llround(static_cast<double>(cents) * factor));
    }

    // Arithmetic and comparison operators
    Money operator+(const Money& o) const { return Money(cents + o.cents); }
    Money operator-(const Money& o) const { return Money(cents - o.cents); }
    bool operator==(const Money& o) const { return cents == o.cents; }
    bool operator!=(const Money& o) const { return cents != o.cents; }
    bool operator<(const Money& o) const { return cents < o.cents; }
    bool operator>(const Money& o) const { return cents > o.cents; }
    bool operator<=(const Money& o) const { return cents <= o.cents; }
    bool operator>=(const Money& o) const { return cents >= o.cents; }

    friend ostream& operator<<(ostream& os, const Money& m) { return os << m.toString(); }
};

#endif // MONEY_H