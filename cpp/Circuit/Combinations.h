#ifndef ELECTRICAL_UTILITIES_PARALLELRESISTANCE_H
#define ELECTRICAL_UTILITIES_PARALLELRESISTANCE_H
#include <vector>

    // DC Resistance
    double ParallelResistance(std::vector<double> R);
    double SeriesResistance(std::vector<double> rList);

    // DC Capacitance
    double ParallelCapacitance(std::vector<double> cList);
    double SeriesCapacitance(std::vector<double> cList);


#endif //ELECTRICAL_UTILITIES_PARALLELRESISTANCE_H
