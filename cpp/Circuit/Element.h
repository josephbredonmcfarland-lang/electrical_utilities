#ifndef ELECTRICAL_UTILITIES_ELEMENT_H
#define ELECTRICAL_UTILITIES_ELEMENT_H
#include <string>

class Element {
public:
    // Component and material value
    std::string id;
    double value;
    // Constructor
    Element(std::string id, double value);
    // Validate inputs
    void validate();
    // Getters
    std::string getId() const;
    double getValue() const;
    virtual std::string getUnit();
    // Setters
};

class Resistor: public Element {
    Resistor(std::string id, double value);
};

class Capacitor: public Element {
    Capacitor(std::string id, double value);
};

class Inductor: public Element {
    Inductor(std::string id, double value);
};



#endif //ELECTRICAL_UTILITIES_ELEMENT_H
