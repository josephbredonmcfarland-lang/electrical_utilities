#include "TIMER_xx555.h"
#include <stdexcept>
#include <fstream>
#include <cmath>

TIMER_xx555::TIMER_xx555(float vcc, float r_a, float c)
    : vcc(vcc), r_a(r_a), c(c) {
    validate();
}

/*
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
    void update_thresholds() {
        v_thresh_low = (1.0f/3.0f)*vcc;
        v_thresh_high = (2.0f/3.0f)*vcc;
    };
    void validate() {
        if (vcc < 5.0f || vcc > 15.0f) {
            throw std::invalid_argument("Vcc is out of range 5V-14V");
        }
        if (r_a <= 0.0f || c <= 0.0f) {
            throw std::invalid_argument("Component values must be positive");
        }
    }
public:
    // Constructor
    TIMER_xx555( float vcc, float r_a, float c)
    : vcc(vcc), r_a(r_a), c(c) {
        validate();
        update_thresholds();
    }
    // Setters
    void set_vcc(float new_vcc) {
        vcc = new_vcc;
        validate();
        update_thresholds();
    }
    void set_r_a(float new_r_a) {
        r_a = new_r_a;
        validate();
    }
    void set_c(float new_c) {
        c = new_c;
        validate();
    }
    // Export to CSV
    void export_to_csv(const std::vector<Sample>& samples, const std::string& filename) const {
        // Open Filestream
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
        // Write to CSV
        file << "time,voltage\n";
        for (const Sample& s : samples) {
            file << s.time << "," << s.voltage << "\n";
        }
    }
};

// Reacts to a signal input; uses a falling edge trigger (v_thresh_low) to trigger pulse
class TIMER_xx555_MONOSTABLE : public TIMER_xx555 {
public:
    // Constructor
    TIMER_xx555_MONOSTABLE( float vcc, float r_a, float c)
        : TIMER_xx555(vcc, r_a, c) {
    }
    // Monostable Operation
    float monostable_pulsewidth() const {
        // Output Pulse Duration (s)
        return 1.1f*r_a*c;
    }
    // Waveform Generators
    std::vector<Sample> generate_signal(const std::vector<Sample>& input_signal) const {
        // Data
        std::vector<Sample> samples;
        samples.reserve(input_signal.size());
        // Logic States
        float high = vcc;
        float low = 0;
        // Output Flags
        bool active_pulse = false;
        float pulse_start_time = 0.0f;
        for (size_t i = 1; i < input_signal.size(); ++i) {
            const Sample& prev = input_signal[i-1];
            const Sample& current = input_signal[i];

            bool falling_edge = (prev.voltage > v_thresh_low && current.voltage <= v_thresh_low);
            if (falling_edge && !active_pulse) {
                active_pulse = true;
                pulse_start_time = current.time;
            }
            if (active_pulse && (current.time - pulse_start_time) >= monostable_pulsewidth()) {
                active_pulse = false;
            }
            float output = active_pulse ? high : low;
            samples.push_back(Sample{current.time, output});
        }
        return samples;
    }
};

// Acts as a free running oscillator whose timing is related to its physical components
class TIMER_xx555_ASTABLE : public TIMER_xx555 {
private:
    float r_b;
public:
    // Constructor
    TIMER_xx555_ASTABLE( float vcc, float r_a, float r_b, float c)
        : TIMER_xx555(vcc, r_a, c), r_b(r_b) {
        validate_r_b();
    }
    // Validate r_b
    void validate_r_b() const {
        if (r_b <= 0.0f) {
            throw std::invalid_argument("Component values must be positive");
        }
    }
    // Setters
    void set_r_b(float new_r_b) {
        r_b = new_r_b;
        validate_r_b();
    }
    // Calculators
    float astable_low_pulsewidth() const {
        // Output Pulse Low (s)
        return 0.693f*r_b*c;
    }
    float astable_high_pulsewidth() const {
        // Output Pulse High (s)
        return 0.693f*(r_a+r_b)*c;
    }
    float astable_pulsewidth() const {
        // Output Pulse Low (s)
        return astable_low_pulsewidth() + astable_high_pulsewidth();
    }
    float astable_frequency() const {
        // Output Frequency (Hz)
        return 1/astable_pulsewidth();
    }
    float driver_duty_cycle() const {
        // Output Driver Duty Cycle
        return astable_low_pulsewidth()/astable_pulsewidth();
    }
    float waveform_duty_cycle() const {
        // Output Waveform Duty Cycle
        return astable_high_pulsewidth()/astable_pulsewidth();
    }
    // Waveform Generators
    std::vector<Sample> generate_signal(float duration, float sample_rate) const {
        // Sample Timing
        if (duration <= 0) {
            throw std::invalid_argument("Duration must be positive");
        }
        if (sample_rate <= 0) {
            throw std::invalid_argument("Sample rate must be positive");
        }
        float t = 0;
        float dt = 1.0f/sample_rate;
        float T = astable_pulsewidth();
        // Data
        int num_samples = static_cast<int>(std::round(duration*sample_rate));
        std::vector<Sample> samples;
        samples.reserve(num_samples);
        // Logic States
        float high = vcc;
        float low = 0;
        float output;
        // Signal Loop
        for (int i = 0; i < num_samples; ++i) {
            // Time Step and Cycled
            t = i*dt;
            float t_mod = fmod(t, T);
            // If t_mod is in HIGH Cycle
            if (t_mod <= astable_high_pulsewidth()) {
                output = high;
            }
            // If t_mod is in LOW Cycle
            else {
                output = low;
            }
            samples.push_back(Sample{t, output});
        }
        return samples;
    }
};
*/


