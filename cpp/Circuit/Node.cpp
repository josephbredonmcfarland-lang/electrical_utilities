#include "Node.h"
#include "Branch.h"
#include <array>

//Constructor
Node::Node(int id, bool referenceNode)
    :id(id), referenceNode(referenceNode) {
}

// Getters
int Node::getid() const {
    return Node::id;
}
double Node::getNodeVoltage() const{
    return Node::nodeVoltage;
}
bool Node::isGround() const{
    return Node::referenceNode;
}
void getBranches(Branch* b) {
}

// Setters
void Node::setVoltage(double voltage) {
    Node::nodeVoltage = voltage;
}
void addBranch(Branch* b) {
    b.push_back(b);
}

//Add Branch
