//
// Created by guy on 06/11/2020.
//

#include "Graph.h"

//todo delete unnecessary CTRS


//DEFAULT CONSTRUCTOR
Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), infectedNodes(matrix.size(), false) {
}

//COPY CONSTRUCTOR
//Graph::Graph(const Graph &graphToCopy) {
//    edges = graphToCopy.edges;
//    infectedNodes = graphToCopy.infectedNodes;
//}

//COPY ASSIGNMENT OPERATOR
//Graph &Graph::operator=(const Graph &graphToCopy) {
//    if (this == &graphToCopy)
//        return *this;
//    clear();
//    edges = graphToCopy.edges;
//    infectedNodes = graphToCopy.infectedNodes;
//    return *this;
//}

//DESTRUCTOR
//Graph::~Graph() {
//    clear();
//}

void Graph::infectNode(int nodeInd) {
    infectedNodes[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd) {
    return infectedNodes[nodeInd];
}

void Graph::isolate(int nodeInd) {
    int edgesSize=edges.size();
    for (int i = 0; i < edgesSize; ++i) {
        edges[nodeInd][i] = 0;
        edges[i][nodeInd] = 0;
    }
}
//todo return vector or something else?
std::vector<int> Graph::getNeighbors(int nodeInd) {
    const std::vector<int> &nodeVector(edges[nodeInd]);
    std::vector<int> neighbors;
    int nodeVectorSize=nodeVector.size();
    for (int i = 0; i < nodeVectorSize; ++i) {
        if (nodeVector[i] == 1)
            neighbors.push_back(i);
    }
    return neighbors;
}

int Graph::getSize() { return edges.size(); }

const std::vector<std::vector<int>> &Graph::getEdges() {
    std::vector<std::vector<int>> &tmpEdges = edges;
    return tmpEdges;
}

const std::vector<int> Graph::getInfected() {
    std::vector<int> infected;
    int infectedNodesSize=infectedNodes.size();
    for (int i = 0; i < infectedNodesSize; ++i) {
        if (infectedNodes[i])
            infected.push_back(i);
    }
    return infected;
}

void Graph::clear() {
    edges.clear();
    infectedNodes.clear();
}

Tree *Graph::bfs(const Session &session, int rootInd) {
    Tree *root = Tree::createTree(session, rootInd);
    std::vector<bool> visited(edges.size(), false);
    visited[rootInd] = true;
    std::queue<Tree *> treesQueue;
    treesQueue.push(root);
    while ((!treesQueue.empty())) {
        Tree *current(treesQueue.front());
        treesQueue.pop();
        std::vector<int> neighbors(getNeighbors(current->getNode()));
        int neighborsSize=neighbors.size();
        for (int i = 0; i < neighborsSize; ++i) {
            int nextNeighbor(neighbors[i]);
            if (!visited[nextNeighbor]) {
                Tree *newChild = Tree::createTree(session, nextNeighbor);
                //current->addChild(*newChild); //todo delete
                current->addChild(newChild);
                //current->addChild((Tree::createTree(session,nextNeighbor)));//todo delete
                visited[nextNeighbor] = true;
                treesQueue.push(newChild);
            }
        }
    }
    return root;
}
