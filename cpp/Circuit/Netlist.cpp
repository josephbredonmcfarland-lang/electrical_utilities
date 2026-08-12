#include "Netlist.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

Netlist::Netlist(std::vector<Branch*> branches): branchList(std::move(branches)){}

void Netlist::parseList(std::vector<Branch*> branches) {
    for (const Branch* branch : branchList) {
        const Element* element = branch->getElement();
        const int id = element->getId();
        const Node* nodeA = branch->getNodeA();
        const Node* nodeB = branch->getNodeB();

    }
}
void Netlist:: addNode(Node* node) {
    nodeList.push_back(node);
}
void Netlist::addBranch(Branch* branch) {
    branchList.push_back(branch);
}
void Netlist::removeBranch(Branch* branch) {
    branchList.erase(std::remove(branchList.begin(), branchList.end(), branch), branchList.end());
}
void Netlist::removeNode(Node* node) {
    nodeList.erase(std::remove(nodeList.begin(), nodeList.end(), node), nodeList.end());
}
