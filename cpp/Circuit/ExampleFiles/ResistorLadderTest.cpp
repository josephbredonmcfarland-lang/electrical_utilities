#include "Netlist.h"
#include "Node.h"
#include "Element.h"

int main() {
    // Nodes
    auto n1 = new Node(1);
    auto n2 = new Node(2);
    auto n3 = new Node(3);
    auto gnd = new ReferenceNode(0);

    // Elements
    auto V1 = new VoltageSource(1, 9.0);
    auto R1 = new Resistor(2, 100);
    auto R2 = new Resistor(3, 220);
    auto R3 = new Resistor(4, 150);
    auto R4 = new Resistor(5, 330);
    auto R5 = new Resistor(6, 470);

    // Branches
    auto b1 = new Branch(1, n1, gnd, V1);  // source: N1 to GND
    auto b2 = new Branch(2, n1, n2, R1);   // ladder series
    auto b3 = new Branch(3, n2, gnd, R2);  // rung to ground
    auto b4 = new Branch(4, n2, n3, R3);   // ladder series
    auto b5 = new Branch(5, n3, gnd, R4);  // rung to ground
    auto b6 = new Branch(6, n3, gnd, R5);  // final rung to ground

    // Assemble netlist
    Netlist netlist({}, {}, {});

    std::vector<Node*> nodes = {n1, n2, n3, gnd};
    std::vector<Branch*> branches = {b1, b2, b3, b4, b5, b6};

    for (Node* n : nodes) {
        netlist.addNode(n);
    }
    for (Branch* b : branches) {
        netlist.addBranch(b);
    }

    netlist.exportList("ResistorLadderTest.txt");

    return 0;
}