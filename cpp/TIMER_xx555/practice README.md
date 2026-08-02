# TIMER_xx555P
   
___

A C++ utility class emulating the NE555 timer IC in monostable or astable mode. The class features calculator, discrete signal generator, and sweep analysis features.  
  
Datasheet reference via Texas Instruments [xx555 Precision Timers](https://www.ti.com/lit/ds/symlink/ne555.pdf)  
___
Two operating modes of the xx555 timer. 
* ASTABLE - the instance acts as a free running oscillator.
* MONOSTABLE - the instance acts as a pulse generator which responds to a falling edge trigger on signal input.
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
## Class: `TIMER_xx555_MONOSTABLE`  
### Constructor 
```cpp
TIMER_xx555(float vcc, float r_a, float c)
```
#### Parameters
| Name | Description             |
|------|-------------------------|
| vcc  | Supply Voltage from 4.5V to 15V |
| r_a  | Timing resistor R_a (Ω) |
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
void set_c(float new_c)
```  
Updates discrete components and validates.
___
### Calculators 
Various `const` member functions which calculate the timing parameters. 
#### Monostable Operation
Pulsewidth value:
```cpp
float monostable_pulsewidth() const
```
`return`: t = 1.1 * R_a * C (seconds)

#### Astable Operation
Pulsewidth values and frequency:
```cpp
float astable_high_pulsewidth() const
```
`return` 
```cpp
float astable_low_pulsewidth() const
```
`return`
```cpp
float astable_pulsewidth() const
```
`return`
```cpp
float astable_frequency() const
```
`return`  

Duty Cycle:
```cpp
float driver_duty_cycle() const
```
`return`
```cpp
float waveform_duty_cycle() const
```
`return`
___
### Author
Joseph William Bredon-McFarland III  
GitHub: [josephbredonmcfarland-lang](https://github.com/josephbredonmcfarland-lang)











