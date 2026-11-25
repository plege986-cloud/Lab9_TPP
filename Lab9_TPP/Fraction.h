#pragma once
#include <iostream>
class Fraction {
    long long n_, d_;
public:
    Fraction(long long n, long long d);
    long long numerator() const { return n_; }
    long long denominator() const { return d_; }
    Fraction operator+(const Fraction& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
};
