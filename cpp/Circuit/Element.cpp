#include "Element.h"
#include <string>
#include <stdexcept>
#include <utility>

// Base Class: Constructor
Element::Element(int id, double value)
    : id(id), value(value) {
    validate();
};
// Validate input value
void Element::validate() const {
    if (value <= 0) {
        throw std::invalid_argument("Value must be positive");
    }
}
// Getters
int Element::getId() const {
    return id;
}
double Element:: getValue() const {
    return value;
}
// Setters
void Element::setValue(double newValue) {
    value = newValue;
}

// Derived Class: Resistor
Resistor::Resistor(int id, double value)
    : Element(id, value) {}
std::string Resistor::getUnit() const {
    return "Ω";
}

// Derived Class: Capacitor
Capacitor::Capacitor(int id, double value)
    : Element(id, value) {}
std::string Capacitor::getUnit() const {
    return "F";
}

// Derived Class: Inductor
Inductor::Inductor(int id, double value)
    : Element(id, value) {}
std::string Inductor::getUnit() const {
    return "H";
}

// Sources
VoltageSource::VoltageSource(int id, double value): Element(id, value) {}
std::string VoltageSource::getUnit() const {
    return "V";
}






