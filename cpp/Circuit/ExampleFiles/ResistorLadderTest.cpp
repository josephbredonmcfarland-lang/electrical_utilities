#include "Netlist.h"
#include "Node.h"
#include "Element.h"

int main() {
    // Nodes
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    ReferenceNode* gnd = new ReferenceNode(0);

    // Elements
    VoltageSource* V1 = new VoltageSource("V1", 9.0);
    Resistor* R1 = new Resistor("R1", 100);
    Resistor* R2 = new Resistor("R2", 220);
    Resistor* R3 = new Resistor("R3", 150);
    Resistor* R4 = new Resistor("R4", 330);
    Resistor* R5 = new Resistor("R5", 470);

    // Branches
    Branch* b1 = new Branch(1, n1, gnd, V1);  // source: N1 to GND
    Branch* b2 = new Branch(2, n1, n2, R1);   // ladder series
    Branch* b3 = new Branch(3, n2, gnd, R2);  // rung to ground
    Branch* b4 = new Branch(4, n2, n3, R3);   // ladder series
    Branch* b5 = new Branch(5, n3, gnd, R4);  // rung to ground
    Branch* b6 = new Branch(6, n3, gnd, R5);  // final rung to ground

    // Assemble netlist
    Netlist netlist({});

    std::vector<Node*> nodes = {n1, n2, n3, gnd};
    std::vector<Branch*> branches = {b1, b2, b3, b4, b5, b6};

    for (Node* n : nodes) {
        netlist.addNode(n);
    }
    for (Branch* b : branches) {
        netlist.addBranch(b);
    }

    netlist.exportList("resistor_ladder.txt");

    return 0;
}