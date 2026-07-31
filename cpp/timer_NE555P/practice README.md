# TIMER_NE555P
Joseph William Bredon-McFarland III  
GitHub: [josephbredonmcfarland-lang](https://github.com/josephbredonmcfarland-lang)   
___

A C++ utility class emulating the NE555 timer IC in monostable or astable mode. The class features calculator, discrete signal generator, and sweep analysis features.  
  
Datasheet reference via Texas Instruments [xx555 Precision Timers](https://www.ti.com/lit/ds/symlink/ne555.pdf)  
___
## Enums
  
### `enum class Mode`
  
```cpp
enum class Mode { ASTABLE, MONOSTABLE };
```

Selects the mode of operation for the instance
* `ASTABLE` - the instance acts as a free running oscillator.
* `MONOSTABLE` - the instance acts as a pulse generator which responds to a falling edge trigger on signal input.
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
## Class: `TIMER_NE555P`  
### Constructor 
```cpp
TIMER_NE555P(Mode mode, float, vcc, float r_a, float r_b, float c)
```
#### Parameters
| Name | Description             |
|------|-------------------------|
| mode | `Mode::ASTABLE` or `Mode::MONOSTABLE` |
| vcc  | Supply Voltage from 4.5V to 15V |
| r_a  | Timing resistor R_a (Ω) |
| r_b  | Timing resistor R_b (Ω) |
| c    | Timing Capacitor (F)    |

**Behavior**: Initializes all supplied values, validates vcc and sets the capacitor voltage thresholds.  
**Throws**: `std::invalid_argument` if `vcc` is out of range.  
___
### Setters
#### Supply Voltage
```cpp
void set_vcc(float new_vcc)
```  
Updates supply voltage, validates new_vcc, and updates threshold voltages.
#### Discrete Components
```cpp
void set_r_a(float new_r_a)
```  
```cpp
void set_r_b(float new_r_b)
```  
```cpp
void set_c(float new_c)
```  
Updates discrete components and revalidates.
___
### Calculators 
Various `const` member functions which calculate the timing parameters. 
#### Monostable Operation
```cpp
float monostable_pulsewidth() const
```
Monostable output pulse duration.   
- Formula: t = 1.1 * R_a * C  
- `return`: pulse duration (s)

#### Astable Operation
```cpp
float astable_high_pulsewidth() const
```
```cpp
float astable_low_pulsewidth() const
```
```cpp
float astable_pulsewidth() const
```
```cpp
float astable_frequency() const
```
```cpp
float driver_duty_cycle() const
```
```cpp
float waveform_duty_cycle() const
```












