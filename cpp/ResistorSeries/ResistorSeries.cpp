#include "ResistorSeries.h"
#include <stdexcept>
#include <vector>
#include <cmath>
#include <fstream>
#include <SigFig.h>

// Constructor
ResistorSeries::ResistorSeries(ESeries series)
    : series(series) {
    Validate();
    Update();
}
// Input Check
void ResistorSeries::Validate() const {}
// Update values
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
// Getters
// Calculate Resistor Values
std::vector<float> ResistorSeries::GetValues() const {
    std::vector<float> values;
    float Rn;
    for (int k = 0; k <= 6; k++) {
        for (int n = 0; n < ResistorSeries::N; n++) {
            Rn = std::pow(10.0f, static_cast<float>(k)) * std::pow(10.0f, static_cast<float>(n)/static_cast<float>(ResistorSeries::N));
            values.push_back(Rn);
        }
    }
    return values;
}
// Get Exponent
int ResistorSeries::GetExponent(float value) const {
    return static_cast<int>(std::floor(std::log10(value)));
}
// Get Prefix Logic
std::string ResistorSeries::GetPrefix(int exponent) const {

    if (exponent < 3) {
        return "";
    }
    else if (exponent <6) {
        return "k";
    }
    else {
        return "M";
    }
}

std::vector<ResistorData> ResistorSeries:: Compile() const{
    ResistorData data;
    std::vector<ResistorData> stream;
    std::vector<float> values = GetValues();
    for (size_t i = 0; i < values.size(); i++) {
        // Normalize Value
        int exponent = GetExponent(values[i]);
        int groupStart = 3 * (exponent / 3);
        float divisor = std::pow(10.0f, static_cast<float>(groupStart));
        // Compile Resistor Data
        data.series = ResistorSeries::series;
        data.value = SigFig(values[i] / divisor, 2);
        data.prefix = GetPrefix(exponent);
        data.unit = "Ω";
        data.tolerance = ResistorSeries::tolerance;
        stream.push_back(data);
    }
    return stream;

}
// Export
std::string ResistorSeries::Series2String(ESeries s) {
    switch (s) {
        case ESeries::E6:   return "E6";
        case ESeries::E12:  return "E12";
        case ESeries::E24:  return "E24";
        case ESeries::E48:  return "E48";
        case ESeries::E96:  return "E96";
        case ESeries::E192: return "E192";
    }
    return "";
}
void ResistorSeries::ExportCSV(std::vector<ResistorData>& stream, const std::string& filename) {
    // Open Filestream
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    // Write to CSV
    file << "Series,Value,Unit,Tolerance\n";
    for (const ResistorData& s : stream) {
        file << Series2String(s.series) << "," << s.value << "," << s.prefix + s.unit << "," << s.tolerance << "\n";
    }

}