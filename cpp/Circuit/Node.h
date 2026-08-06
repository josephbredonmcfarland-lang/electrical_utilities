#ifndef ELECTRICAL_UTILITIES_NODE_H
#define ELECTRICAL_UTILITIES_NODE_H
#include <vector>

class Branch;

class Node {
public:
    // Netlist Values
    int id;
    double nodeVoltage;
    bool isReference;
    // Connected Branches
    std::vector<Branch*> branches;
    // Constructor
    Node(int id);
    // Getters
    bool isGround() const;
    int getId() const;
    double getNodeVoltage() const;
    const std::vector<Branch*>& getBranches() const;
    // Setters
    void setVoltage(double voltage);
    void addBranch(Branch* branch);
};

class ReferenceNode : public Node {
public:
    ReferenceNode(int id);
};


#endif //ELECTRICAL_UTILITIES_NODE_H
