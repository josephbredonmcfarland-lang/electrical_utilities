#include "ResistorSeries.h"
#include <stdexcept>
#include <vector>
#include <cmath>


ResistorSeries::ResistorSeries(ESeries series)
    : series(series) {
    Validate();
    Update();
}

void ResistorSeries::Validate() const {}

void ResistorSeries::Update() {
    switch (series) {
        case ESeries::E6:
            ResistorSeries:: N = 6;
            ResistorSeries::tolerance = 0.2f;
            break;
        case ESeries::E12:
            ResistorSeries:: N = 12;
            ResistorSeries::tolerance = 0.1f;
            break;
        case ESeries::E24:
            ResistorSeries:: N = 24;
            ResistorSeries::tolerance = 0.05f;
            break;
        case ESeries::E48:
            ResistorSeries:: N = 48;
            ResistorSeries::tolerance = 0.02f;
            break;
        case ESeries::E96:
            ResistorSeries:: N = 96;
            ResistorSeries::tolerance = 0.01f;
            break;
        case ESeries::E192:
            ResistorSeries:: N = 192;
            ResistorSeries::tolerance = 0.005f;
            break;
    }
}

std::vector<float> ResistorSeries::GetValues() const {
    std::vector<float> values;
    float Rn;
    // Calculate Resistor Values
    for (int k = 0; k <= 6; k++) {
        for (int n = 0; n < ResistorSeries::N; n++) {
            Rn = std::pow(10.0f, static_cast<float>(k)) * std::pow(10.0f, static_cast<float>(n)/static_cast<float>(ResistorSeries::N));
            values.push_back(Rn);
        }
    }
    return values;
}
