#include "ParallelSum.h"
#include <stdexcept>


double ParallelSum(std::initializer_list<double> list) {
    double num = 0;
    for (const double x : list) {
        if (x == 0) {
            throw std::invalid_argument("List value cannot be 0.");
        }
        num += 1.0/x;
    }
    return 1.0/num;
}

