#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree {
public:
    Tree(int rootLabel);                         //CONSTRUCTOR
    Tree(const Tree &treeToCopy);               //COPY CONSTRUCTOR
    virtual ~Tree();                           //DESTRUCTOR
    Tree &operator=(const Tree &treeToCopy);  //COPY ASSIGNMENT OPERATOR
    Tree &operator=(Tree &&treeToCopy);       // MOVE ASSIGNMENT OPERATOR
    Tree(Tree&& treeToCopy);                       // MOVE CONSTRUCTOR

    void addChild(const Tree &child);
    void addChild(Tree *child);
    static Tree *createTree(const Session &session, int rootLabel);
    virtual int traceTree() = 0;

    virtual Tree *clone() const = 0;
    int getNode() const;
    virtual void setValuesAs(const Tree& tree);

protected:
    int node;
    void clear();
    std::vector<Tree *> children;

private:
    int findIndex( Tree *toAdd, int n);

};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle); //DEFAULT CONSTRUCTOR
    CycleTree(const CycleTree &cycleTreeToCopy); //COPY CONSTRUCTOR
    CycleTree &operator=(const CycleTree &cycleTreeToCopy);  //COPY ASSIGNMENT OPERATOR
    virtual ~CycleTree()=default;            //DESTRUCTOR

    virtual int traceTree();
    virtual int traceTree(int cycle);

    virtual Tree *clone() const;
    int getCycle() const;

private:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    MaxRankTree(const MaxRankTree &maxRankTreeToCopy); //COPY CONSTRUCTOR
    MaxRankTree &operator=(const MaxRankTree &maxRankTreeToCopy);  //COPY ASSIGNMENT OPERATOR
    virtual ~MaxRankTree()=default;         //DESTRUCTOR
    virtual int traceTree();

    virtual Tree *clone() const;

private:
    MaxRankTree* traceTree(MaxRankTree* child);

};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);    // CONSTRUCTOR

    RootTree(const RootTree &rootTreeToCopy);              //COPY CONSTRUCTOR
    RootTree &operator=(const RootTree &rootTreeToCopy);  //COPY ASSIGNMENT OPERATOR
    virtual ~RootTree()=default;         //DESTRUCTOR

    virtual int traceTree();

    virtual Tree *clone() const;
};

#endif
