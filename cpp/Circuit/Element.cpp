#include "Element.h"
#include <string>
#include <stdexcept>
#include <utility>

// Base Class: Constructor
Element::Element(std::string id, double value)
    : id(std::move(id)), value(value) {
    validate();
};
// Validate input value
void Element::validate() const {
    if (value <= 0) {
        throw std::invalid_argument("Value must be positive");
    }
}
// Getters
std::string Element::getId() const {
    return id;
}
double Element:: getValue() const {
    return value;
}

// Derived Class: Resistor
Resistor::Resistor(const std::string& id, double value)
    : Element(id, value) {};
// Get Ohms
std::string Resistor::getUnit() const {
    return "Ω";
}

// Derived Class: Resistor
Capacitor::Capacitor(const std::string& id, double value)
    : Element(id, value) {};
// Get Ohms
    std::string Capacitor::getUnit() const {
    return "F";
}

// Derived Class: Resistor
Inductor::Inductor(const std::string& id, double value)
    : Element(id, value) {};
// Get Ohms
std::string Inductor::getUnit() const {
    return "L";
}





