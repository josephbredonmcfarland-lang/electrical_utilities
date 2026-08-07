#include "Netlist.h"

Netlist::Netlist(std::vector<Branch*> branches): branchList(std::move(branches)){}

void Netlist:: addNode(Node* node) {
    nodeList.push_back(node);
}
void Netlist::addBranch(Branch* branch) {
    branchList.push_back(branch);
}
void removeBranch(Branch* branch) {
    branchList.remove(branch);
}
void removeNode(Node* node) {
    nodeList.remove(node);
}
