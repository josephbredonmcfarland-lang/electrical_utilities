#include "Element.h"
#include <string>
#include <stdexcept>

// Constructor
Element::Element(std::string id, double value)
    : id(id), value(value), unit("") {
    validate();
};
// Validate input value
void Element::validate() {
    if (value <= 0) {
        throw std::invalid_argument("Value must be positive");
    }
}

Resistor::Resistor(std::string id, double value)
    : Element(id, value, unit("Ω")) {

};

