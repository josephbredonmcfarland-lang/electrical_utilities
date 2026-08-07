#ifndef ELECTRICAL_UTILITIES_NETLIST_H
#define ELECTRICAL_UTILITIES_NETLIST_H
#include <vector>
#include "Branch.h"
#include "Node.h"

class Netlist {
public:

    std::vector<Branch*> branchList;
    std::vector<Node*> nodeList;

    Netlist(std::vector<Branch*> branches);

    void parseBranches(std::vector<Branch*> branches);

    void addNode(Node*);
    void addBranch(Branch*);
    void removeBranch(Branch*);
    void removeNode(Node*);





};


#endif //ELECTRICAL_UTILITIES_NETLIST_H
