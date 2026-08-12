#include "Netlist.h"
#include <vector>

Netlist::Netlist(std::vector<Branch*> branches): branchList(std::move(branches)){}

void Netlist:: addNode(Node* node) {
    nodeList.push_back(node);
}
void Netlist::addBranch(Branch* branch) {
    branchList.push_back(branch);
}
void Netlist::removeBranch(Branch* branch) {
    branchList.erase(std::remove(branchList.begin(), branchList.end(), branch);
}
void Netlist::removeNode(Node* node) {
    nodeList.erase(nodeList.begin(), nodeList.end(), node);
}
