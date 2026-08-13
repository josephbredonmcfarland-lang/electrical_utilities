#ifndef ELECTRICAL_UTILITIES_ELEMENT_H
#define ELECTRICAL_UTILITIES_ELEMENT_H
#include <string>

// Base Class
class Element {
public:
    // Component and material value
    int id;
    double value;
    // Constructor
    Element(int id, double value);
    // Virtual Destructor
    virtual ~Element() = default;
    // Validate inputs
    void validate() const;
    // Getters
    int getId() const;
    double getValue() const;
    virtual std::string getUnit() const= 0;
    // Setters
    void setValue(double newValue);
};

// Passive Elements
class Resistor: public Element {
public:
    Resistor(int id, double value);
    std::string getUnit() const override;
};
class Capacitor: public Element {
public:
    Capacitor(int id, double value);
    std::string getUnit() const override;
};
class Inductor: public Element {
public:
    Inductor(int id, double value);
    std::string getUnit() const override;
};
// Ideal Sources
class VoltageSource: public Element {
public:
    VoltageSource(int id, double value);
    std::string getUnit() const override;
};

#endif //ELECTRICAL_UTILITIES_ELEMENT_H
