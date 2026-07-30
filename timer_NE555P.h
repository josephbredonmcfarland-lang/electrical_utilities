#ifndef ELECTRICAL_UTILITIES_TIMER_NE555P_H
#define ELECTRICAL_UTILITIES_TIMER_NE555P_H


enum class Mode {ASTABLE, MONOSTABLE};

class timer_NE555P {

private:
    float t;
    // Operation Mode
    Mode mode;
    // Supply Voltage and Discrete Components
    float vcc;
    float r_a;
    float r_b;
    float c;
    // Voltage Threshold (Capacitor Output)
    float v_thresh_low = (1.0f/3.0f)*vcc;
    float v_thresh_high = (2.0f/3.0f)*vcc;

public:
    // Monostable Operation
    float monostable_pulsewidth() {
        // Output Pulse Duration (s)
        float tw = 1.1*r_a*c;
        return tw;
    }

    // Astable Operation
    float astable_low_pulsewidth() {
        // Output Pulse Low (s)
        float tl = 0.639*(r_a + 2*r_b)*c;
        return tl;
    }
    float astable_high_pulsewidth() {
        // Output Pulse High (s)
        float th =0.639*r_a*c;
        return th;
    }
    float  astable_total_pulsewidth() {
        // Output Pulse Low (s)
        float T = astable_low_pulsewidth() + astable_high_pulsewidth();
        return T;
    }
    float astable_frequency() {
        // Output Frequency (Hz)
        float f = 1/astable_total_pulsewidth();
        return f;
    }
    float driver_duty_cycle() {
        float ddc = astable_low_pulsewidth()/astable_total_pulsewidth();
        return ddc;
    }
    float waveform_duty_cycle() {
        // Waveform Duty Cycle
        float wdc = astable_high_pulsewidth()/astable_total_pulsewidth();
        return wdc;
    }
};


#endif //ELECTRICAL_UTILITIES_TIMER_NE555P_H
