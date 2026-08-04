#include "Combinations.h"
#include <numeric>
#include "ReciprocalSum.h"

double ParallelResistance(std::initializer_list<double> rList) {
    return ReciprocalSum(rList);
}

double SeriesResistance(std::initializer_list<double> rList) {
    return std::accumulate(rList.begin(), rList.end(), 0.0);
}

double ParallelCapacitance(std::initializer_list<double> cList) {
    return std::accumulate(cList.begin(), cList.end(), 0.0);;
}

double SeriesCapacitance(std::initializer_list<double> cList) {
    return ReciprocalSum(cList);
}