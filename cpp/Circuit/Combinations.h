#ifndef ELECTRICAL_UTILITIES_PARALLELRESISTANCE_H
#define ELECTRICAL_UTILITIES_PARALLELRESISTANCE_H
#include <vector>

    // DC Resistance
    double ParallelResistance(double R1, double R2);
    double ParallelResistance(std::vector<double> R);
    double SeriesResistance(double R1, double R2);
    double SeriesResistance(std::vector<double> rList);

    // DC Capacitance
    double ParallelCapacitance(double C1, double C2);
    double ParallelCapacitance(std::vector<double> cList);
    double SeriesCapacitance(double C1, double C2);
    double SeriesCapacitance(std::vector<double> rList);


#endif //ELECTRICAL_UTILITIES_PARALLELRESISTANCE_H
