# timer_NE555P

A C++ utility class modeling the NE555 timer IC in astable or monostable configuration. Provides timing calculators, signal generation for use as a modular block in circuit simulations, and (planned) parameter sweep analysis.

Datasheet reference: [NE555 (TI)](https://www.ti.com/lit/ds/symlink/ne555.pdf)

---

## Enums

### `enum class Mode`
```cpp
enum class Mode { ASTABLE, MONOSTABLE };
```
Selects which of the two standard 555 operating configurations this instance represents.

- `ASTABLE` — free-running oscillator, self-sustaining output, no external trigger required.
- `MONOSTABLE` — one-shot pulse generator, output only responds to a falling-edge trigger on an input signal.

---

## Structs

### `struct Sample`
```cpp
struct Sample {
    float time;    // (s)
    float voltage; // (V)
};
```
A single timestamped voltage sample. This is the unit of data both waveform generators produce and consume — a `std::vector<Sample>` represents a full signal over time, suitable for plotting or feeding into another component's input.

---

## Class: `timer_NE555P`

### Constructor

```cpp
timer_NE555P(Mode mode, float vcc, float r_a, float r_b, float c)
```

**Parameters**
| Name | Description |
|---|---|
| `mode` | `Mode::ASTABLE` or `Mode::MONOSTABLE` |
| `vcc` | Supply voltage (V). Must be between 4.5 and 15. |
| `r_a` | Timing resistor R_a (Ω) |
| `r_b` | Timing resistor R_b (Ω). May be 0 when `mode == MONOSTABLE`, since monostable operation does not use R_b. |
| `c` | Timing capacitor (F) |

**Throws**: `std::invalid_argument` if `vcc` is out of range.

**Behavior**: Initializes all supplied values via the member initializer list, then validates `vcc` and derives the capacitor voltage thresholds (`v_thresh_low`, `v_thresh_high`) before the object is usable.

---

### Calculator methods

All calculator methods are `const` — they compute a value from the object's current state and never modify it.

#### `float monostable_pulsewidth() const`
Output pulse duration for monostable operation.
**Formula**: `t = 1.1 * R_a * C`
**Returns**: pulse duration in seconds.

#### `float astable_low_pulsewidth() const`
Duration of the LOW portion of the astable output cycle.
**Formula**: `t_low = 0.693 * R_b * C`

#### `float astable_high_pulsewidth() const`
Duration of the HIGH portion of the astable output cycle.
**Formula**: `t_high = 0.693 * (R_a + R_b) * C`

#### `float astable_pulsewidth() const`
Total period of one astable cycle.
**Formula**: `T = t_high + t_low`

#### `float astable_frequency() const`
Oscillation frequency of the astable output.
**Formula**: `f = 1 / T`

#### `float driver_duty_cycle() const`
Fraction of the cycle the internal discharge transistor is driving (LOW time / total period).
**Formula**: `t_low / T`

#### `float waveform_duty_cycle() const`
Fraction of the cycle the output waveform itself is HIGH.
**Formula**: `t_high / T`

---

### Setters

Each setter re-validates state after mutating it, so the object can never be left in an invalid configuration mid-use.

#### `void set_vcc(float new_vcc)`
Updates the supply voltage. Re-runs `validate()` (range check) and `update_thresholds()` (since the capacitor thresholds depend on `vcc`).

#### `void set_r_a(float new_r_a)` / `void set_r_b(float new_r_b)` / `void set_c(float new_c)`
Update the respective timing component. Re-runs `validate()`.

---

### Signal generators

These are the two "modular block" methods — they produce a `std::vector<Sample>` representing this timer's output over time, in a form suitable for plotting or feeding into another component.

They differ fundamentally in *kind*: `generate_astable_signal` is a **source** (autonomous — needs no external input, output is fully determined by the object's own parameters). `generate_monostable_signal` is a **transfer function** (non-autonomous — output is a response to an external input signal).

#### `std::vector<Sample> generate_astable_signal(float duration, float sample_rate) const`

**Parameters**
| Name | Description |
|---|---|
| `duration` | Total length of the simulation window, in seconds |
| `sample_rate` | Samples per second |

**Returns**: A vector of `Sample`s spanning `[0, duration)`, alternating between `vcc` and `0.0f` according to the astable HIGH/LOW timing.

**Mechanism**: For each sample time `t`, computes `t_mod = fmod(t, astable_pulsewidth())` — the position within the current cycle — and outputs `vcc` if `t_mod` falls within the HIGH portion of the cycle, `0.0f` otherwise. Requires no memory of past samples; each point is computed independently.

#### `std::vector<Sample> generate_monostable_signal(const std::vector<Sample>& input_signal) const`

**Parameters**
| Name | Description |
|---|---|
| `input_signal` | An existing signal (e.g. from another component, or a hand-built trigger waveform) to scan for trigger events |

**Returns**: A vector of `Sample`s, one per input sample (after the first), reflecting this timer's response to detected triggers.

**Mechanism**: Scans consecutive pairs of input samples for a falling edge across `v_thresh_low` (voltage was above the threshold, then at-or-below it). On each detected edge — provided no pulse is already active — starts a pulse: output holds `vcc` for `monostable_pulsewidth()` seconds, then returns to `0.0f`. A new trigger arriving while a pulse is already active is ignored, matching real NE555 non-retriggerable behavior.

---

## Status

- [x] Calculator layer
- [x] Astable signal generation
- [x] Monostable signal generation
- [ ] Full input validation (`r_a`, `r_b`, `c` positivity)
- [ ] Getters for `r_a`, `r_b`, `c`, `mode`
- [ ] General-purpose parameter sweep / analysis function
- [ ] Split into `.h` / `.cpp`
