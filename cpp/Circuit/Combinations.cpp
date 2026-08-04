#include "Combinations.h"
#include <cmath>


double reciprocal
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
double SeriesResistance(double R1, double R2) {
    return R1 + R2;
}

double SeriesResistance(std::vector<double> rList) {
    double num = 0;
    for (const double& r : rList) {
        num += r;
    }
    return num;
}

double ParallelCapacitance(double C1, double C2) {
    return SeriesResistance(C1, C2);
}
double ParallelCapacitance(std::vector<double> rList) {
    return SeriesResistance(rList);
}
double SeriesCapacitance(double C1, double C2) {
    return ParallelResistance(C1, C2);
}
double SeriesCapacitance(std::vector<double> rList) {
    return ParallelResistance(rList);
}