#ifndef ELECTRICAL_UTILITIES_PARALLELRESISTANCE_H
#define ELECTRICAL_UTILITIES_PARALLELRESISTANCE_H
#include <initializer_list>


    // DC Resistance
    double ParallelResistance(std::initializer_list<double> rList);
    double SeriesResistance(std::initializer_list<double> rList);

    // DC Capacitance
    double ParallelCapacitance(std::initializer_list<double> cList);
    double SeriesCapacitance(std::initializer_list<double> cList);


#endif //ELECTRICAL_UTILITIES_PARALLELRESISTANCE_H
