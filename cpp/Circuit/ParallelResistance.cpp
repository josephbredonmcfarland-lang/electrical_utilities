#include "ParallelResistance.h"
#include <cmath>

double ParallelResistance(double R1, double R2) {
    double R = std::pow((1/R1) + (1/R2), -1);
    return R;
}

double ParallelResistance(std::vector<double> rList) {
    double num =0;
    for (const double& r : rList) {
        num += 1/r;
    }
    return std::pow(num, -1);
}