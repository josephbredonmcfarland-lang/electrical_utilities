#include "HarmonicSum.h"
#include <cmath>
#include <stdexcept>

double HarmonicSum(std::initializer_list<double> list) {
    double num = 0;
    for (const double x : list) {
        if (x == 0) {
            throw std::invalid_argument("List value cannot be 0.");
        }
        num += 1/x;
    }
    return 1/num;
}

