// 555 Timer Utility
// Datasheet: https://www.ti.com/lit/ds/symlink/ne555.pdf?ts=1785379495739&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FNE555%252Fpart-details%252FNE555DR

#ifndef ELECTRICAL_UTILITIES_TIMER_NE555P_H
#define ELECTRICAL_UTILITIES_TIMER_NE555P_H
#include <stdexcept>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

// Sample Container
struct Sample {
    float time; // (s)
    float voltage; // (V)
};

// Base Class 555 Timer
class TIMER_xx555 {
protected:
    float vcc, r_a, c, v_thresh_low, v_thresh_high;
    void update_thresholds();
    void validate();
public:
    // Constructor
    TIMER_xx555( float vcc, float r_a, float c);
    // Setters
    void set_vcc(float new_vcc);
    void set_r_a(float new_r_a);
    void set_c(float new_c);
    // Export to CSV
    void export_to_csv(const std::vector<Sample>& samples, const std::string& filename) const;

};

// Reacts to a signal input; uses a falling edge trigger (v_thresh_low) to trigger pulse
class TIMER_xx555_MONOSTABLE : public TIMER_xx555 {
public:
    // Constructor
    TIMER_xx555_MONOSTABLE( float vcc, float r_a, float c);
    // Monostable Operation
    float monostable_pulsewidth() const;
    // Waveform Generators
    std::vector<Sample> generate_signal(const std::vector<Sample>& input_signal) const;
};

// Acts as a free running oscillator whose timing is related to its physical components
class TIMER_xx555_ASTABLE : public TIMER_xx555 {
private:
    float r_b;
public:
    // Constructor
    TIMER_xx555_ASTABLE( float vcc, float r_a, float r_b, float c);
    // Validate r_b
    void validate_r_b() const;
    // Setters
    void set_r_b(float new_r_b);
    // Calculators
    float astable_low_pulsewidth();
    float astable_high_pulsewidth() const;
    float astable_pulsewidth() const;
    float astable_frequency() const;
    float driver_duty_cycle() const;
    float waveform_duty_cycle() const;
    // Waveform Generators
    std::vector<Sample> generate_signal(float duration, float sample_rate) const;
};

#endif //ELECTRICAL_UTILITIES_TIMER_NE555P_H
