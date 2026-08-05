#include "CarToPol.h"
#include <complex>

Polar CarToPol(const std::complex<double> car) {
    Polar pol;
    double magnitude = std::abs(car);
    double direction = std::arg(car);
    pol.magnitude = magnitude;
    pol.direction = direction;
    return pol;
}
