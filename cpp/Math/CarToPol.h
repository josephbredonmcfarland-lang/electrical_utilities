#ifndef ELECTRICAL_UTILITIES_CARTOPOL_H
#define ELECTRICAL_UTILITIES_CARTOPOL_H
#include <complex>

    struct Polar {
        double magnitude;
        double direction;
    };

    Polar CarToPol(std::complex<double> car);

#endif //ELECTRICAL_UTILITIES_CARTOPOL_H
