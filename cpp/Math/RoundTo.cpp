// Round to a significant figure
#include "RoundTo.h"
#include <cmath>

double RoundTo(double num, int sigfig) {
    if (num == 0) {
        return 0;
    }
    int magnitude = std::floor(std::log10(std::fabs(num)));
    int shift = sigfig -1 - magnitude;
    double scale = std::pow(10, shift);
    double scalenum = num*scale;
    double rounded = std::round(scalenum);
    double result = rounded / scale;
    return result;
}

