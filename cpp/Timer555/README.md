# TIMER_xx555

___

A C++ utility class emulating the NE555 timer IC in monostable or astable mode. The class features calculator, discrete signal generator, and sweep analysis features.

Datasheet reference via Texas Instruments [xx555 Precision Timers](https://www.ti.com/lit/ds/symlink/ne555.pdf)
___
Two operating modes of the xx555 timer.
* ASTABLE: the instance acts as a free running oscillator.
* MONOSTABLE: the instance acts as a pulse generator which responds to a falling edge trigger on signal input.
___
## Structs
### `struct Sample`
```cpp
struct Sample {
    float time;    // (s)
    float voltage; // (V)
};
```
The Sample struct acts like a container for a single time stamped sample of the output.

`std::vector<Sample>` is built from these samples and represents the signal over time. This vector may be the output or serve as the input for the following discrete signal generators.
___
## Class: `Timer555` (Base Class)
`TIMER_xx555_MONOSTABLE` and `TIMER_xx555_ASTABLE` both inherit from this class. It owns the shared state (`vcc`, `r_a`, `c`) and shared behavior (validation, threshold calculation, CSV export) common to every operating mode. It is not intended to be instantiated directly.
### Constructor
```cpp
TIMER_xx555(float vcc, float r_a, float c)
```
#### Parameters
| Name | Description                     |
|------|----------------------------------|
| vcc  | Supply Voltage from 5V to 15V   |
| r_a  | Timing resistor R_a (Ω)         |
| c    | Timing Capacitor (F)            |

**Behavior**: Initializes all supplied values, validates `vcc`/`r_a`/`c`, and sets the capacitor voltage thresholds.  

**Throws**: `std::invalid_argument` if `vcc` is out of range, or if `r_a`/`c` is not positive.
___
### Setters
#### Supply Voltage
```cpp
void set_vcc(float new_vcc)
```
Updates supply voltage, validates `new_vcc`, and updates threshold voltages.
#### Discrete Components
```cpp
void set_r_a(float new_r_a)
```
```cpp
void set_c(float new_c)
```
Updates discrete components and validates.
___
### CSV Export
```cpp
static void export_to_csv(const std::vector<Sample>& samples, const std::string& filename)
```
Writes a `time,voltage` header row followed by one row per `Sample` to `filename`.
Static — does not require a constructed timer instance, since it operates only on the `samples` and `filename` passed in.
**Throws**: `std::runtime_error` if the file cannot be opened.
___
## Class: `TIMER_xx555_MONOSTABLE`
Extends `Timer555`. Reacts to a signal input; a falling edge below the low voltage threshold triggers a single output pulse of fixed duration. Inherits `set_vcc`, `set_r_a`, `set_c`, and `export_to_csv` unchanged from the base class.
### Constructor
```cpp
TIMER_xx555_MONOSTABLE(float vcc, float r_a, float c)
```
Same parameters as the base class constructor — passed straight through.
___
### Calculators
```cpp
float pulsewidth() const
```
`return`: t = 1.1 × R_a × C (seconds) — the duration of the output pulse once triggered.
___
### Waveform Generators
```cpp
std::vector<Sample> generate_signal(const std::vector<Sample>& input_signal) const
```
#### Parameters
| Name | Description |
|------|-------------|
| input_signal | The trigger signal to evaluate for falling edges |

**Behavior**: Scans `input_signal` for a falling edge below the low voltage threshold. On trigger, holds the output high for `pulsewidth()` seconds, then returns to low, watching for the next trigger.
**Returns**: A `std::vector<Sample>` the same length as `input_signal` minus one (the first input sample has no prior sample to compare against, so it produces no corresponding output).
___
## Class: `TIMER_xx555_ASTABLE`
Extends `Timer555`. Acts as a free running oscillator whose timing is set entirely by its physical components — no trigger input required. Inherits `set_vcc`, `set_r_a`, `set_c`, and `export_to_csv` unchanged from the base class.
### Constructor
```cpp
TIMER_xx555_ASTABLE(float vcc, float r_a, float r_b, float c)
```
#### Parameters
| Name | Description             |
|------|--------------------------|
| r_b  | Timing resistor R_b (Ω) |

(`vcc`, `r_a`, `c` — same as base class.)

**Throws**: `std::invalid_argument` if `r_b` is not positive, in addition to the base class's own validation.
___
### Setters
#### Discrete Component
```cpp
void set_r_b(float new_r_b)
```
Updates `r_b` and validates independently of the base class's `validate()`.
___
### Calculators
Pulsewidth values and frequency:
```cpp
float pulsewidth_high() const
```
`return`: 0.693 × (R_a + R_b) × C (seconds) — duration of the output's high phase.
```cpp
float pulsewidth_low() const
```
`return`: 0.693 × R_b × C (seconds) — duration of the output's low phase.
```cpp
float pulsewidth() const
```
`return`: `pulsewidth_high()` + `pulsewidth_low()` — full period (seconds).
```cpp
float frequency() const
```
`return`: 1 / `pulsewidth()` (Hz).

Duty Cycle:
```cpp
float dutycycle_driver() const
```
`return`: `pulsewidth_low()` / `pulsewidth()` — fraction of the period the internal driver transistor is conducting.
```cpp
float dutycycle_waveform() const
```
`return`: `pulsewidth_high()` / `pulsewidth()` — fraction of the period the output waveform reads high.
___
### Waveform Generators
```cpp
std::vector<Sample> generate_signal(float duration, float sample_rate) const
```
#### Parameters
| Name | Description |
|------|-------------|
| duration | Total length of signal to generate (s) |
| sample_rate | Number of samples per second (Hz) |

**Behavior**: Generates a fixed-rate sampling of the free-running output waveform over `duration`, cycling between high and low according to `pulsewidth_high()`/`pulsewidth_low()`.
**Returns**: A `std::vector<Sample>` of length `round(duration × sample_rate)`.
**Throws**: `std::invalid_argument` if `duration` or `sample_rate` is not positive.
___
### Author
Joseph William Bredon-McFarland III  
GitHub: [josephbredonmcfarland-lang](https://github.com/josephbredonmcfarland-lang)