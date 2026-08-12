#include "Netlist.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <Element.h>
#include <stdexcept>

Netlist::Netlist(std::vector<Branch*> branches): branchList(std::move(branches)){}

void Netlist::exportList(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file " + filename);
    }
    for (const Branch* branch : branchList) {
        Node* nodeA = branch->getNodeA();
        Node* nodeB = branch->getNodeB();
        file << branch->element->getId() << " "
             << branch->element->getValue() << branch->element->getUnit() << " "
             << (nodeA->isGround() ? "GND" : "N" +std::to_string(nodeA->getId())) << " "
             << (nodeB->isGround() ? "GND" : "N" +std::to_string(nodeB->getId())) << " "
             << "\n";
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
