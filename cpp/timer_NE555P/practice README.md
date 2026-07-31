# TIMER_NE555P
___
Joseph William Bredon-McFarland III  
GitHub: josephbredonmcfarland-lang  
Gmail: josephbredonmcfarland@gmail.com  
___

A C++ utility class emulating the NE555 timer IC in monostable or astable mode. The class features calculator, discrete signal generator, and sweep analysis features.  
  
Datasheet reference via Texas Instruments [xx555 Precision Timers](https://www.ti.com/lit/ds/symlink/ne555.pdf?ts=1785467898823&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FNE555%253Futm_source%253Dsupplyframe%2526utm_medium%253DSEP%2526utm_campaign%253Dnot_alldatasheet%2526DCM%253Dyes)  
___
## Enums
  
### `enum class Mode`
  
```cpp
enum class Mode { ASTABLE, MONOSTABLE }
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
## Class: TIMER_NE555P









