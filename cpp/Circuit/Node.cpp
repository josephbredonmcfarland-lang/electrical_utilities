#include "Node.h"
#include "Branch.h"

//Constructor
Node::Node(int id, bool referenceNode)
    :id(id), referenceNode(referenceNode), nodeVoltage(0) {}
// Getters
int Node::getId() const {
    return id;
}
double Node::getNodeVoltage() const{
    return Node::nodeVoltage;
}
bool Node::isGround() const{
    return referenceNode;
}
const std::vector<Branch*>& Node::getBranches() const {
    return Node::branch;
}

// Setters
void Node::setVoltage(double voltage) {
    Node::nodeVoltage = voltage;
}
void Node::addBranch(Branch* b) {
    Node::branch.push_back(b);
}
