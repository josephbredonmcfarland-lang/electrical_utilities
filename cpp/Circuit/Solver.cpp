#include "Solver.h"
#include "Element.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>

Solver::Solver(Netlist& netlist) : netlist(netlist) {}

void Solver::buildIndices() {
    nodeIndex.clear();
    sourceIndex.clear();

    numNodes = 0;
    for (Node* node : netlist.nodeList) {
        if (!node->isGround()) {
            nodeIndex[node] = numNodes++;
        }
    }

    numSources = 0;
    for (Branch* branch : netlist.branchList) {
        if (dynamic_cast<VoltageSource*>(branch->getElement())) {
            sourceIndex[branch] = numSources++;
        }
    }
}

void Solver::stampResistor(Branch* branch, double conductance) {
    Node* a = branch->getNodeA();
    Node* b = branch->getNodeB();
    bool aGround = a->isGround();
    bool bGround = b->isGround();

    if (!aGround) {
        int ia = nodeIndex[a];
        A[ia][ia] += conductance;
    }
    if (!bGround) {
        int ib = nodeIndex[b];
        A[ib][ib] += conductance;
    }
    if (!aGround && !bGround) {
        int ia = nodeIndex[a];
        int ib = nodeIndex[b];
        A[ia][ib] -= conductance;
        A[ib][ia] -= conductance;
    }
}

void Solver::stampVoltageSource(Branch* branch, int sourceIdx, double value) {
    Node* a = branch->getNodeA();
    Node* b = branch->getNodeB();
    bool aGround = a->isGround();
    bool bGround = b->isGround();
    int row = numNodes + sourceIdx;

    if (!aGround) {
        int ia = nodeIndex[a];
        A[row][ia] += 1.0;
        A[ia][row] += 1.0;
    }
    if (!bGround) {
        int ib = nodeIndex[b];
        A[row][ib] -= 1.0;
        A[ib][row] -= 1.0;
    }
    z[row] = value;
}

void Solver::solve() {
    buildIndices();
    int size = numNodes + numSources;
    if (size == 0) {
        throw std::runtime_error("Solver: no solvable unknowns (no non-ground nodes or sources).");
    }

    A.assign(size, std::vector<double>(size, 0.0));
    z.assign(size, 0.0);

    for (Branch* branch : netlist.branchList) {
        Element* element = branch->getElement();
        if (auto* r = dynamic_cast<Resistor*>(element)) {
            stampResistor(branch, 1.0 / r->getValue());
        } else if (auto* v = dynamic_cast<VoltageSource*>(element)) {
            stampVoltageSource(branch, sourceIndex[branch], v->getValue());
        } else {
            throw std::runtime_error(
                "Solver: unsupported element type for DC operating point (" + element->getName() + ")");
        }
    }

    gaussianEliminate();
}

void Solver::gaussianEliminate() {
    int n = static_cast<int>(A.size());
    x.assign(n, 0.0);

    for (int col = 0; col < n; ++col) {
        int pivotRow = col;
        double maxVal = std::fabs(A[col][col]);
        for (int row = col + 1; row < n; ++row) {
            if (std::fabs(A[row][col]) > maxVal) {
                maxVal = std::fabs(A[row][col]);
                pivotRow = row;
            }
        }
        if (maxVal < 1e-12) {
            throw std::runtime_error(
                "Solver: singular matrix - circuit may be underconstrained "
                "(floating node, or no path to ground).");
        }
        std::swap(A[col], A[pivotRow]);
        std::swap(z[col], z[pivotRow]);

        for (int row = col + 1; row < n; ++row) {
            double factor = A[row][col] / A[col][col];
            for (int k = col; k < n; ++k) {
                A[row][k] -= factor * A[col][k];
            }
            z[row] -= factor * z[col];
        }
    }

    for (int row = n - 1; row >= 0; --row) {
        double sum = z[row];
        for (int k = row + 1; k < n; ++k) {
            sum -= A[row][k] * x[k];
        }
        x[row] = sum / A[row][row];
    }
}

double Solver::getNodeVoltage(Node* node) const {
    if (node->isGround()) {
        return 0.0;
    }
    auto it = nodeIndex.find(node);
    if (it == nodeIndex.end()) {
        throw std::runtime_error("Solver: node not part of the solved netlist.");
    }
    return x[it->second];
}

double Solver::getSourceCurrent(Branch* branch) const {
    auto it = sourceIndex.find(branch);
    if (it == sourceIndex.end()) {
        throw std::runtime_error("Solver: branch is not a voltage source branch.");
    }
    return x[numNodes + it->second];
}