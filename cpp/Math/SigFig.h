#ifndef ELECTRICAL_UTILITIES_SIGFIG_H
#define ELECTRICAL_UTILITIES_SIGFIG_H
#pragma once

class SigFig {
private:
    double num;
    int sigfig;
public:
  static double SigFig(double num, int sigfig);
};


#endif //ELECTRICAL_UTILITIES_SIGFIG_H
