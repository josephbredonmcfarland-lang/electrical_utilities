#include "PolToCar.h"

std::complex<double> PolToCar(Polar pol) {
    return std::polar(pol.magnitude, pol.direction);
}


