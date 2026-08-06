#include "Branch.h"
#include "Node.h"
#include "Element.h"

// Constructor
Branch::Branch(int id, Node* nodeA, Node* nodeB, Element* element)
:id(id), nodeA(nodeA), nodeB(nodeB), element(element), current(0.0) {}
// Getters
int Branch::getId() const {
    return id;
}
Node* Branch::getNodeA() const {
    return nodeA;
}
Node* Branch::getNodeB() const {
    return nodeB;
}
Element* Branch::getElement() const {
    return element;
}
double Branch::getCurrent() const {
    return current;
}
// Setters
void Branch::setCurrent(double current) {
    Branch::current = current;
}


