#include "Branch.h"

// Constructor
Branch::Branch(int id, Node* nodeA, Node* nodeB, Element* element)
:id(id), nodeA(nodeA), nodeB(nodeB), element(element), current(0.0) {}

int Branch::getId() const {
    return id;
}
int Branch::getNodeA() const {
    return nodeA;
}
int Branch::getNodeB() const {
    return nodeB;
}
Element* Branch::getElement() const {
    return element;
}
double Branch::getCurrent() const {
    return current;
}
void Branch::setCurrent(double current) {
    Branch::current = current;
}


