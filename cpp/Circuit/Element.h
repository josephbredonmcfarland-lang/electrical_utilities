#ifndef ELECTRICAL_UTILITIES_ELEMENT_H
#define ELECTRICAL_UTILITIES_ELEMENT_H
#include <string>

class Element {
public:
    std::string id;
    double value;
    std::string unit;
    Element(std::string id, double value);
    void validate();
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
