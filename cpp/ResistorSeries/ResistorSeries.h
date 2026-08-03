// Generate the Resistor Series and export to CSV
// Website Reference https://www.rfcafe.com/references/electrical/resistor-values.htm

#ifndef ELECTRICAL_UTILITIES_RESISTORSERIES_H
#define ELECTRICAL_UTILITIES_RESISTORSERIES_H
#include <string>
#include <vector>

enum class ESeries {
    E6, // 20%
    E12, // 10%
    E24, // 5%
    E48, // 2%
    E96, // 1%
    E192 // 0.05%
};

struct ResistorData {
    ESeries series;
    float value;
    std::string prefix;
    std::string unit = "Ω";
    float tolerance;
};

class ResistorSeries {

protected:
    ESeries series; // Series Name
    int N; // Value per Decade
    float tolerance;

public:
    // Constructor
    explicit ResistorSeries(ESeries series);
    // Validate Inputs
    void Validate() const;
    // Update Values
    void Update();
    // Generate Series();
    std::vector<float> GetValues() const;
    // Prefix Logic
    std::string GetPrefix(int exponent) const;
    std::vector<ResistorData> Compile() const;
    int GetExponent(float value) const;
    std::string Series2String(ESeries s) const;
    void ExportCSV(std::vector<ResistorData> stream, std::string filename) const;

};

#endif //ELECTRICAL_UTILITIES_RESISTORSERIES_H
