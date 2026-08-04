#include "../ResistorSeries.h"
#include <array>

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
