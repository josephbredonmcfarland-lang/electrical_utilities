#ifndef ELECTRICAL_UTILITIES_NODE_H
#define ELECTRICAL_UTILITIES_NODE_H
#include <vector>

class Branch{};

class Node {
public:

    // Netlist Values
    int id;
    double nodeVoltage;
    bool referenceNode;

    // Connected Branches
    std::vector<Branch*> branch;

    // Constructor
    Node(int id, bool isReference);

    // Getters
    int getId() const;
    double getNodeVoltage() const;
    bool isGround() const;
    const std::vector<Branch*>& getBranches() const;

    // Setters
    void setVoltage(double voltage);
    void addBranch(Branch* branch);
};


#endif //ELECTRICAL_UTILITIES_NODE_H
