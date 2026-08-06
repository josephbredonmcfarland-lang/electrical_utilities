#include "Branch.h"

// Constructor
Branch::Branch(int id, Node* nodeA, Node* nodeB, Element* element)
:id(id), nodeA(nodeA), nodeB(nodeB), element(element), current(0.0) {}

int getId() const {
    return id;
}
int getNodeA() const {
    return nodeA;
}
int getNodeB() const {
    return Branch::nodeB;
}
double getCurrent() const {
    return Branch::current;
}
void setCurrent(double current) {
    Branch::current = current;
}


