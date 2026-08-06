#ifndef ELECTRICAL_UTILITIES_ELEMENT_H
#define ELECTRICAL_UTILITIES_ELEMENT_H
#include <string>


// Base Class
class Element {
public:
    // Component and material value
    std::string id;
    double value;
    // Constructor
    Element(std::string id, double value);
    // Virtual Destructor
    virtual ~Element() = default;
    // Validate inputs
    void validate() const;
    // Getters
    std::string getId() const;
    double getValue() const;
    virtual std::string getUnit() const= 0;
    // Setters
    static void setValue(double newValue);

};

// Passive Elements
class Resistor: public Element {
public:
    Resistor(const std::string& id, double value);
    std::string getUnit() const override;
};
class Capacitor: public Element {
public:
    Capacitor(const std::string& id, double value);
    std::string getUnit() const override;
};
class Inductor: public Element {
public:
    Inductor(const std::string& id, double value);
    std::string getUnit() const override;
};
// Sources
class VoltageSource: public Element {
public:
    VoltageSource(const std::string& id, double value);
    std::string getUnit() const override;
};


#endif //ELECTRICAL_UTILITIES_ELEMENT_H
