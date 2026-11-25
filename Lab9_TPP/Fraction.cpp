#include "Fraction.h"
#include <numeric>
#include <stdexcept>
Fraction::Fraction(long long n, long long d)
{
    if (!d)
        throw std::invalid_argument("Zero denominator");
    if (d < 0)
    {
        n = -n;
        d = -d;
    }
    auto g = std::gcd(n, d);
    n_ = n / g;
    d_ = d / g;
}
Fraction Fraction::operator+(const Fraction &o) const
{
    return Fraction(n_ * o.d_ + o.n_ * d_, d_ * o.d_);
}
std::ostream &operator<<(std::ostream &out, const Fraction &f)
{
    return out << f.n_ << '/' << f.d_;
}
