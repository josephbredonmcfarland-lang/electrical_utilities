#include "Element.h"
#include <string>
#include <stdexcept>

// Constructor
Element::Element(std::string id, double value)
    : id(id), value(value) {
    validate();
};
// Validate input value
void Element::validate() {
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


Resistor::Resistor(std::string id, double value)
    : Element(id, value) {

};

