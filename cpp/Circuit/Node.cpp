#include <iostream>
#include <vector>
#include "Node.h"
#include "Branch.h"

//Constructor
Node::Node(int id)
    : id(id), nodeVoltage(0.0), isReference(false){}

// Getters
int Node::getId() const {
    return id;
}
double Node::getNodeVoltage() const{
    return nodeVoltage;
}
bool Node::isGround() const{
    return isReference;
}
const std::vector<Branch*>& Node::getBranches() const {
    return Node::branches;
}
// Setters:
void Node::setVoltage(double voltage) {
    Node::nodeVoltage = voltage;
}
void Node::addBranch(Branch* b) {
    Node::branches.push_back(b);
}

// Reference node derived class and virtual function:
ReferenceNode::ReferenceNode(int id): Node(id){}
void ReferenceNode::setVoltage(double voltage) {
    throw std::logic_error("Cannot set reference node voltage");
}
