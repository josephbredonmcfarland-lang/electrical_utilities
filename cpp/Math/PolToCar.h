#ifndef ELECTRICAL_UTILITIES_POLTOCAR_H
#define ELECTRICAL_UTILITIES_POLTOCAR_H
#include <complex>
#include

struct Polar {
    double magnitude;
    double direction;
};

std::complex<double> PolToCar(Polar pol);

#endif //ELECTRICAL_UTILITIES_POLTOCAR_H
