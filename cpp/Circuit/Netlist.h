#ifndef ELECTRICAL_UTILITIES_NETLIST_H
#define ELECTRICAL_UTILITIES_NETLIST_H
#include <vector>
#include "Branch.h"
#include "Node.h"
#include "Element.h"
#include <string>


class Netlist {
public:
    std::vector<Element*> elementList;
    std::vector<Branch*> branchList;
    std::vector<Node*> nodeList;
    Netlist(std::vector<Node*> nodeList, std::vector<Branch*> branchList, std::vector<Element*> elementList);
    ~Netlist();
    void exportList(const std::string& filename) const;
    void addElement(Element*);
    void addNode(Node*);
    void addBranch(Branch*);
    void removeBranch(Branch*);
    void removeNode(Node*);
};

#endif //ELECTRICAL_UTILITIES_NETLIST_H
