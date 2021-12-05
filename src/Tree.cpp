// Created by spl211 on 05/11/2020.

#include "Tree.h"
#include "Session.h"


// *************************************  class Tree  **************************
Tree::Tree(int rootLabel) : node(rootLabel), children() {}        //CONSTRUCTOR
// Rule of 3
Tree::Tree(const Tree &treeToCopy) : node(treeToCopy.node), children() {
    int toCopyChildrenSize = treeToCopy.children.size();
    for (int i = 0; i < toCopyChildrenSize; ++i) {
        children.push_back(treeToCopy.children[i]->clone());
    }
}               //COPY CONSTRUCTOR
Tree::~Tree() {
    clear();
}                                    //DESTRUCTOR
Tree &Tree::operator=(const Tree &treeToCopy) {

    if (this != &treeToCopy) {
        node = treeToCopy.node;
        int thisChildrenSize = children.size();
        for (int i = 0; i < thisChildrenSize; ++i) {         //destructing all 'my' children
            delete children[i];
        }
        children.clear();
        int toCopyChildrenSize = treeToCopy.children.size();
        for (int i = 0; i < toCopyChildrenSize; ++i) {
            children.push_back(treeToCopy.children[i]->clone());
        }
    }

    return *this;
}       //COPY ASSIGNMENT OPERATOR
//Rule of 5
Tree::Tree(Tree &&treeToCopy) : node(treeToCopy.node), children() {
    int treeToCopySize = treeToCopy.children.size();
    for (int i = 0; i < treeToCopySize; ++i) {
        children.push_back(treeToCopy.children[i]);
        treeToCopy.children[i] = nullptr;
    }
    treeToCopy.children.clear();
}                   // MOVE CONSTRUCTOR
Tree &Tree::operator=(Tree &&treeToCopy) {

    if (getNode() != treeToCopy.getNode()) {
        node = treeToCopy.getNode();
        clear();
        for (Tree *tree: treeToCopy.children) {
            children.push_back(tree);
        }
        treeToCopy.children.clear();
    }
    return *this;
}   // MOVE ASSIGNMENT OPERATOR

void Tree::addChild(const Tree &child) {
    Tree *toAdd = child.clone();
    addChild(toAdd);
}

void Tree::addChild(Tree *child) {
    int i = findIndex(child, child->getNode());
    if (i != -1) {
        children.push_back(nullptr);
        for (int j = children.size() - 2; j >= i; --j) {
            children[j + 1] = children[j];
        }
        children[i] = child;
    }
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    if (rootLabel < 0)
        throw "rootLabel must be non-negative";
    switch (session.getTreeType()) {
        case MaxRank:
            return new MaxRankTree(rootLabel);
        case Cycle:
            return new CycleTree(rootLabel, session.getCycle());
        case Root:
            return new RootTree(rootLabel);
    }
    throw "no valid TreeType in session";
}

int Tree::getNode() const {
    return node;
}

int Tree::findIndex(Tree *toAdd, int nodeNumber) {
    int i = 0;
    if (children.empty() || nodeNumber >= children[children.size() -
                                                   1]->getNode()) {      //check if needs to be added at the end of the array
        i = -1;
        children.push_back(toAdd);
    } else if (nodeNumber <= children[0]->getNode())        //check if needs to be added at index 0
        i = 0;

    else {
        bool found = false;
        int childrenSize = children.size();
        for (i = 1; i < childrenSize && !found; ++i) {
            if (nodeNumber >= children[i - 1]->getNode() && nodeNumber <= children[i]->getNode())
                found = true;
        }
        i--;
    }
    return i;
}

void Tree::clear() {       //destructing all 'my' children
    int childrenSize = children.size();
    for (int i = 0; i < childrenSize; ++i)
        if (children[i] != nullptr) {
            delete children[i];
            children[i] = nullptr;
        }

    children.clear();
}

void Tree::setValuesAs(const Tree &tree) {
    node = tree.getNode();
    clear();
    int treeChildrenSize = tree.children.size();
    for (int i = 0; i < treeChildrenSize; ++i) {
        children.push_back(tree.children[i]->clone());
    }
}


//********************* class CycleTree: public Tree ****************************
CycleTree::CycleTree(int _rootLabel, int _currCycle) : Tree(_rootLabel), currCycle(_currCycle) {}   //CONSTRUCTOR
// Rule of 3ish
CycleTree::CycleTree(const CycleTree &cycleTreeToCopy) : Tree(cycleTreeToCopy), currCycle(cycleTreeToCopy.currCycle) {
}         //COPY CONSTRUCTOR
CycleTree &CycleTree::operator=(const CycleTree &cycleTreeToCopy) {
    if (this != &cycleTreeToCopy) {
        currCycle = cycleTreeToCopy.getCycle();
        Tree::setValuesAs(cycleTreeToCopy);
    }

    return *this;
}                   //COPY ASSIGNMENT OPERATOR

int CycleTree::traceTree() {
    return traceTree(getCycle());
}

int CycleTree::traceTree(int cycle) {
    if (cycle == 0 || children.empty())
        return getNode();

    return ((CycleTree *) children[0])->traceTree(cycle - 1);
}

Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}

int CycleTree::getCycle() const {
    return currCycle;
}


// ************************  class MaxRankTree: public Tree ***********************
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}         // CONSTRUCTOR
// Rule of 3ish
MaxRankTree::MaxRankTree(const MaxRankTree &maxRankTreeToCopy) : Tree(maxRankTreeToCopy) {} //COPY CONSTRUCTOR
MaxRankTree &MaxRankTree::operator=(const MaxRankTree &maxRankTreeToCopy) {

    if (this != &maxRankTreeToCopy)
        Tree::setValuesAs(maxRankTreeToCopy);

    return *this;
}   //COPY ASSIGNMENT OPERATOR

int MaxRankTree::traceTree() {
    return traceTree(this)->getNode();
}

MaxRankTree *MaxRankTree::traceTree(MaxRankTree *child) {
    if (children.empty())
        return child;
    MaxRankTree *max = child;
    int maxRank = max->children.size();
    int childChildrenSize = child->children.size();
    for (int i = 0; i < childChildrenSize; ++i) {
        MaxRankTree *temp = traceTree((MaxRankTree *) child->children[i]);
        int tempChildrenSize = temp->children.size();
        if (maxRank < tempChildrenSize)
            max = temp;
        maxRank = max->children.size();
    }

    return max;
}


Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}


// ************************  class RootTree: public Tree ****************************
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}         // CONSTRUCTOR
// Rule of 3ish
RootTree::RootTree(const RootTree &rootTreeToCopy) : Tree(rootTreeToCopy) {}           //COPY CONSTRUCTOR
RootTree &RootTree::operator=(const RootTree &rootTreeToCopy) {
    if (this != &rootTreeToCopy)
        Tree::setValuesAs(rootTreeToCopy);
    return *this;
}   //COPY ASSIGNMENT OPERATOR

int RootTree::traceTree() {
    return getNode();
}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}