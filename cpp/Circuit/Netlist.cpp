#include "Netlist.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>

Netlist::Netlist(std::vector<Node*> nodeList, std::vector<Branch*> branchList, std::vector<Element*> elementList)
: nodeList(std::move(nodeList)), branchList(std::move(branchList)), elementList(std::move(elementList)){}

Netlist::~Netlist() {
    for (Branch* branch : branchList) {
        delete branch;
    }
    for (Node* node : nodeList) {
        delete node;
    }
    for (Element* element : elementList) {
        delete element;
    }
}
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
void Netlist::addNode(Node* node) {
    nodeList.push_back(node);
}
void Netlist::addBranch(Branch* branch) {
    branchList.push_back(branch);
    branch->getNodeA()->addBranch(branch);
    branch->getNodeB()->addBranch(branch);
}
void Netlist::addElement(Element* element) {
    elementList.push_back(element);
}
void Netlist::removeBranch(Branch* branch) {
    branch->getNodeA()->removeBranch(branch);
    branch->getNodeB()->removeBranch(branch);
    branchList.erase(std::remove(branchList.begin(), branchList.end(), branch), branchList.end());
    delete branch;
}
void Netlist::removeNode(Node* node) {
    if (!node->getBranches().empty()) {
        throw std::runtime_error("Cannot remove node: branches are still attached. Remove those branches first.");
    }
    nodeList.erase(std::remove(nodeList.begin(), nodeList.end(), node), nodeList.end());
    delete node;
}