#include "Approximator.h"
#include <cmath>
#include <stdexcept>
#include <utility>
// Educational adaptation of Netlib frac: https://www.netlib.org/c/frac
// Keeps goto and rounded intermediate error; restricted to safe demonstration inputs.
Fraction legacyApproximate(double v, double error)
{
    if (!std::isfinite(v) || !std::isfinite(error) || v < 3e-10 || v > 1000000 || error < 1e-10)
        throw std::invalid_argument("Legacy demo range");
    long long n = static_cast<long long>(v), d = 1, N = n + 1, D = 1;
    double r = 0, epsilon = 0, m = 1;
    int steps = 0;
    goto three;
one:
    if (r <= 1)
        r = 1 / r;
    if (!std::isfinite(r) || r > 1e9 || r < 0 || ++steps > 100)
        throw std::runtime_error("Legacy limit");
    if ((long double)N + n * (long double)r + n > 1e12 ||
        (long double)D + d * (long double)r + d > 1e12)
        throw std::runtime_error("Legacy limit");
    N += n * static_cast<long long>(r);
    D += d * static_cast<long long>(r);
    n += N;
    d += D;
three:
    r = 0;
    if (v * d == n)
        goto four;
    r = (N - v * D) / (v * d - n);
    if (r > 1)
        goto four;
    std::swap(N, n);
    std::swap(D, d);
four:
    epsilon = std::abs(1.0 - n / (v * d));
    if (epsilon <= error)
        return {n, d};
    m = 1;
    do
    {
        m *= 10;
    } while (m * epsilon < 1);
    epsilon = std::floor(0.5 + m * epsilon) / m;
    if (epsilon <= error)
        return {n, d};
    if (r != 0)
        goto one;
    throw std::runtime_error("Legacy approximation failed");
}
