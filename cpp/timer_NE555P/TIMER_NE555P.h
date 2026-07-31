// Joseph William Bredon-McFarland III 7/30/2026
// GitHub: josephbredonmcfarland-lang
// 555 Timer Utility
// Datasheet: https://www.ti.com/lit/ds/symlink/ne555.pdf?ts=1785379495739&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FNE555%252Fpart-details%252FNE555DR

#ifndef ELECTRICAL_UTILITIES_TIMER_NE555P_H
#define ELECTRICAL_UTILITIES_TIMER_NE555P_H
#include <stdexcept>
#include <vector>
#include <cmath>

// Mode and Output State
enum class Mode {ASTABLE, MONOSTABLE};

// Sample Container
struct Sample {
    float time; // (s)
    float voltage; // (V)
};

class TIMER_NE555P {
private:
    // Operation Mode
    Mode mode;
    // Supply Voltage and Discrete Components
    float vcc;
    float r_a;
    float r_b;
    float c;
    // Voltage Threshold (Capacitor Output)
    float v_thresh_low;
    float v_thresh_high;

    // Update Thresholds
    void update_thresholds() {
        v_thresh_low = (1.0f/3.0f)*vcc;
        v_thresh_high = (2.0f/3.0f)*vcc;
    }
    // Validate Inputs
    void validate() const {
        if (vcc < 4.5f || vcc > 15.0f) {
            throw std::invalid_argument("Vcc is out of range");
        }
    }

public:
    // Constructor
    timer_NE555P(Mode mode, float vcc, float r_a, float r_b, float c)
        :mode(mode), vcc(vcc), r_a(r_a), r_b(r_b), c(c) {
        validate();
        update_thresholds();
    }

    // Monostable Operation
    float monostable_pulsewidth() const {
        // Output Pulse Duration (s)
        return 1.1f*r_a*c;
    }

    // Astable Operation
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
    void set_r_b(float new_r_b) {
        r_b = new_r_b;
        validate();
    }
    void set_c(float new_c) {
        c = new_c;
        validate();
    }

    // Waveform Generators
    std::vector<Sample> generate_astable_signal(float duration, float sample_rate) const {
        // Sample Timing
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
    std::vector<Sample> generate_monostable_signal(const std::vector<Sample>& input_signal) const {
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




#endif //ELECTRICAL_UTILITIES_TIMER_NE555P_H
