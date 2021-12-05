#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include "Tree.h"

class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix);    //DEFAULT CONSTRUCTOR
    //Graph(const Graph& graphToCopy);     //COPY CONSTRUCTOR
    //Graph &operator=(const Graph& graphToCopy);  //COPY ASSIGNMENT OPERATOR
    //virtual ~Graph();   //DESTRUCTOR

    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    void isolate(int nodeInd);

    std::vector<int> getNeighbors(int nodeInd);

    Tree *bfs(const Session &session, int rootInd);

    int getSize();
    const std::vector<std::vector<int>>& getEdges();
    const std::vector<int> getInfected();

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infectedNodes;


    void clear();

};

#endif
