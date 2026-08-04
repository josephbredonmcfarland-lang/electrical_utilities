#include "ReciprocalSum.h"
#include <cmath>

double ReciprocalSum(std::initializer_list<double> list) {
    double num = 0;
    for (const double& x : list) {
        num += 1/x;
    }
    return std::pow(num, -1);
}

