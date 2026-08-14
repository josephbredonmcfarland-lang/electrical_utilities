#ifndef ELECTRICAL_UTILITIES_SOLVER_H
#define ELECTRICAL_UTILITIES_SOLVER_H

#include "Netlist.h"
#include <unordered_map>
#include <vector>

// Solves a resistive DC network (resistors + ideal voltage sources)
// using Modified Nodal Analysis (MNA).
//
// Convention: for a voltage source Branch, nodeA is treated as the
// "+" terminal and nodeB as the "-" terminal, i.e. V(nodeA) - V(nodeB)
// = source value.
class Solver {
public:
    explicit Solver(Netlist& netlist);

    void solve();
    double getNodeVoltage(Node* node) const;
    double getSourceCurrent(Branch* branch) const;

private:
    Netlist& netlist;
    std::unordered_map<Node*, int> nodeIndex;
    std::unordered_map<Branch*, int> sourceIndex;
    std::vector<std::vector<double>> A;
    std::vector<double> z;
    std::vector<double> x;
    int numNodes = 0;
    int numSources = 0;

    void buildIndices();
    void stampResistor(Branch* branch, double conductance);
    void stampVoltageSource(Branch* branch, int sourceIdx, double value);
    void gaussianEliminate();
};

#endif //ELECTRICAL_UTILITIES_SOLVER_H