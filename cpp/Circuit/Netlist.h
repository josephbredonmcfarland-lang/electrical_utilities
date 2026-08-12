#ifndef ELECTRICAL_UTILITIES_NETLIST_H
#define ELECTRICAL_UTILITIES_NETLIST_H
#include <vector>
#include "Branch.h"
#include "Node.h"
#include <string>


class Netlist {
public:
    std::vector<Branch*> branchList;
    std::vector<Node*> nodeList;
    Netlist(std::vector<Branch*> branches);
    void exportList(const std::vector<Branch*>& branches, const std::string& filename) const;
    void addNode(Node*);
    void addBranch(Branch*);
    void removeBranch(Branch*);
    void removeNode(Node*);
};

#endif //ELECTRICAL_UTILITIES_NETLIST_H
