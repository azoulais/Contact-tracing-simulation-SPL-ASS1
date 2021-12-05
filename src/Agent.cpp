//
// Created by guy on 06/11/2020.
//
#include "Agent.h"


//*******************    CTR ********************
Agent::Agent() {}

//*******************    CTR ********************
ContactTracer::ContactTracer() {}

void ContactTracer::act(Session &session) {
    //deque first infected
    int nextInfected(session.dequeueInfected());
    if (nextInfected == -1)        //there is no infected node
        return;
    else {
        //create bfs->trace->isolate node
        Graph &g(session.getGraph());
        Tree *bfsTree = g.bfs(session, nextInfected);
        int nodeToIsolate(bfsTree->traceTree());
        g.isolate(nodeToIsolate);
        delete bfsTree;
    }
}

Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}

//*******************    CTR ********************
Virus::Virus(int nodeInd) : nodeInd(nodeInd) {}

void Virus::act(Session &session) {
    Graph &g(session.getGraph());
    //infect itself
    if (!g.isInfected(nodeInd)) {
        g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    //spread to freevirus neighbor
    int virusFreeNeighbor = -1;
    std::vector<int> neighbors(g.getNeighbors(nodeInd));
    const std::vector<bool> &viruses(session.getViruses());
    int neighborsSize=neighbors.size();
    for (int i = 0; i < neighborsSize; ++i) {
        if (!viruses[neighbors[i]]) {
            virusFreeNeighbor = neighbors[i];
            break;
        }
    }
    if (virusFreeNeighbor != -1) {    //exist virusFree neighbor
        Virus newVirus(virusFreeNeighbor);
        session.setNewVirus(virusFreeNeighbor);
        session.addAgent(newVirus);
    }
}

Agent *Virus::clone() const {
    return new Virus(*this);
}



