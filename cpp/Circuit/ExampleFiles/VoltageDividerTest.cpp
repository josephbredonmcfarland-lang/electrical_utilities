#include "Netlist.h"
#include "Node.h"
#include "Element.h"

int main() {
    // Building the circuit
    // Nodes
    auto n0 = new Node(1);
    auto n1 = new Node(2);
    auto gnd = new ReferenceNode(0);
    // Elements
    auto V1 = new VoltageSource(1, 9);
    auto R1 = new Resistor(1, 100);
    auto R2 = new Resistor(2, 300);
    // Branches
    auto b0 = new Branch(0, gnd, n0, V1);
    auto b1 = new Branch(1, n0,n1,R1);
    auto b2 = new Branch(2, n1,gnd,R2);
    // Compiling list of pointers
    std::vector<Node*> nodeList = {n0, n1, gnd};
    std::vector<Branch*> branchList = {b0, b1, b2};
    std::vector<Element*> elementList = {V1, R1, R2};
    // Bring the information into the netlist
    Netlist netlist = Netlist(nodeList, branchList, elementList);
    // Export Netlist
    netlist.exportList("VoltageDividerTest.txt");







}