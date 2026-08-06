#ifndef ELECTRICAL_UTILITIES_BRANCH_H
#define ELECTRICAL_UTILITIES_BRANCH_H

class Node;
class Element;

class Branch {
public:

    // Netlist
    int id;
    Node* nodeA;
    Node* nodeB;
    Element* element;
    double current;

    // Constructor
    Branch(int id, Node* nodeA, Node* nodeB, Element* element);

    // Getters
    int getId() const;
    Node* getNodeA() const;
    Node* getNodeB() const;
    Element* getElement() const;
    double getCurrent() const;

    // Setters
    void setCurrent(double current);


};


#endif //ELECTRICAL_UTILITIES_BRANCH_H
