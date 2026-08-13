#include "Netlist.h"
#include "Node.h"
#include "Element.h"

int main() {
    // Nodes
    auto n0 = new Node(0);
    auto n1 = new Node(1);
    auto gnd = new ReferenceNode(0);
    // Elements
    auto V1 = new VoltageSource("V1", 9);
    auto R1 = new Resistor("R1", 100);
    auto R2 = new Resistor("R2", 300);
    // Branches
    auto b0 = new Branch(0, gnd, n0, V1);
    auto b1 = new Branch(1, n0,n1,R1);
    auto b2 = new Branch(2, n1,gnd,R2);





}