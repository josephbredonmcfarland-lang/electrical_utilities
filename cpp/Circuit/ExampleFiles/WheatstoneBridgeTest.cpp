#include "Netlist.h"
#include "Node.h"
#include "Element.h"
#include "Solver.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

// Wheatstone bridge:
//
//         n1 (+10V)
//        /        \
//      R1          R2
//      /            \
//    n2 ---- R5 ---- n3    (R5 is the bridge resistor)
//      \            /
//      R3          R4
//        \        /
//           GND
//
// Balanced when R1/R3 == R2/R4 -> bridge carries zero current,
// V(n2) == V(n3), independent of R5's value. This is a topology
// series/parallel collapsing cannot solve (R5 bridges two otherwise
// parallel divider branches), but MNA handles it directly.

int main() {
    auto n1 = new Node(1);
    auto n2 = new Node(2);
    auto n3 = new Node(3);
    auto gnd = new ReferenceNode(0);

    auto V1 = new VoltageSource(1, 10.0);
    auto R1 = new Resistor(1, 100.0);
    auto R2 = new Resistor(2, 150.0);
    auto R3 = new Resistor(3, 200.0);
    auto R4 = new Resistor(4, 300.0);
    auto R5 = new Resistor(5, 150.0);  // bridge resistor - arbitrary value

    auto b0 = new Branch(0, n1, gnd, V1);
    auto b1 = new Branch(1, n1, n2, R1);
    auto b2 = new Branch(2, n1, n3, R2);
    auto b3 = new Branch(3, n2, gnd, R3);
    auto b4 = new Branch(4, n3, gnd, R4);
    auto b5 = new Branch(5, n2, n3, R5);   // the bridge

    std::vector<Node*> nodeList = {n1, n2, n3, gnd};
    std::vector<Branch*> branchList = {b0, b1, b2, b3, b4, b5};
    std::vector<Element*> elementList = {V1, R1, R2, R3, R4, R5};

    Netlist netlist(nodeList, branchList, elementList);
    netlist.exportList("BridgeTest_netlist.txt");

    Solver solver(netlist);
    solver.solve();

    double vn1 = solver.getNodeVoltage(n1);
    double vn2 = solver.getNodeVoltage(n2);
    double vn3 = solver.getNodeVoltage(n3);
    double bridgeCurrent = (vn2 - vn3) / R5->getValue();
    double sourceCurrent = solver.getSourceCurrent(b0);

    std::ofstream results("BridgeTest_results.txt");
    if (!results.is_open()) {
        throw std::runtime_error("Cannot open results file");
    }
    results << std::fixed << std::setprecision(6);
    results << "V(n1)         = " << vn1 << " V\n";
    results << "V(n2)         = " << vn2 << " V  (expect 6.666667)\n";
    results << "V(n3)         = " << vn3 << " V  (expect 6.666667)\n";
    results << "I(R5, bridge) = " << bridgeCurrent << " A  (expect ~0.000000)\n";
    results << "I(V1)         = " << sourceCurrent << " A\n";
    results.close();

    std::cout << "Netlist written to BridgeTest_netlist.txt\n";
    std::cout << "Results written to BridgeTest_results.txt\n";

    return 0;
}