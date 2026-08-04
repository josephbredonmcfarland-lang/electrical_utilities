#include "ResistorSeries/ResistorSeries.h"
#include <array>
#include <iostream>
#include <ostream>
#include <SigFig.h>

int main() {
    constexpr std::array<ESeries, 6> E = {
        ESeries:: E6, ESeries:: E12,ESeries:: E24,ESeries:: E48,ESeries:: E96,ESeries:: E192
    };
    for (const ESeries& e : E) {
        ResistorSeries series(e);
        std::vector<ResistorData> data = series.Compile();
        ResistorSeries::ExportCSV(data,  ResistorSeries::Series2String(e) + "_Series.csv");
    }
    return 0;
}


/*
    //Resistor Series
    constexpr std::array<ESeries, 6> E = {
        ESeries:: E6, ESeries:: E12,ESeries:: E24,ESeries:: E48,ESeries:: E96,ESeries:: E192
    };
    for (const ESeries& e : E) {
        ResistorSeries series(e);
        std::vector<ResistorData> data = series.Compile();
        ResistorSeries::ExportCSV(data,  ResistorSeries::Series2String(e) + "_Series.csv");
    }
    return 0;
*/

/*
    //SigFig Test
    // Test Cases
    double num = 46.89;
    double rounded = SigFig(num, 3);
    std::cout << num << " is rounded to " << rounded << std::endl;

    num = 46.89;
    rounded = SigFig(num, 2);
    std::cout << num << " is rounded to " << rounded << std::endl;

    num = -46.89;
    rounded = SigFig(num, 3);
    std::cout << num << " is rounded to " << rounded << std::endl;

    num = 4689;
    rounded =  SigFig(num, 1);
    std::cout << num << " is rounded to " << rounded << std::endl;

    return 0;
    */