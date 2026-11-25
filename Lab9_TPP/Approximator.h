#pragma once
#include "Fraction.h"
class Approximator {
public:
    Fraction approximate(double value, double tolerance) const;
};
Fraction legacyApproximate(double value, double tolerance);
