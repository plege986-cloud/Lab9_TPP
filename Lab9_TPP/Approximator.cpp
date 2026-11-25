#include "Approximator.h"
#include <cmath>
#include <stdexcept>
#include <utility>
Fraction Approximator::approximate(double v, double tolerance) const {
    if (!std::isfinite(v) || !std::isfinite(tolerance) || v < 3e-10 || v > 4e10 || tolerance < 0) throw std::invalid_argument("Invalid input");
    long long n = static_cast<long long>(v), d = 1, N = n+1, D = 1;
    for (int i=0; i<1000; ++i) {
        if (v*d == n) return {n,d};
        double r = (N-v*D)/(v*d-n);
        if (r <= 1) { std::swap(n,N); std::swap(d,D); }
        double e = std::abs(1.0-n/(v*d));
        if (e <= tolerance) return {n,d};
        if (r <= 1) r = 1/r;
        if (!std::isfinite(r) || r > 1e12 || r < 0) break;
        auto k = static_cast<long long>(r);
        if (std::abs((long double)N+n*(long double)k+n)>1e15 || (long double)D+d*(long double)k+d>1e15) break;
        N += n*k; D += d*k; n += N; d += D;
    }
    throw std::runtime_error("Requested precision cannot be achieved safely");
}
