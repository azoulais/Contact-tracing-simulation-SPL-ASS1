#ifndef SESSION_H_
#define SESSION_H_

#include <queue>
#include <vector>
#include <string>
#include "string"
#include "Graph.h"
#include "Agent.h"

using namespace std;


class Agent;

enum TreeType {
    Cycle,
    MaxRank,
    Root
};

class Session {
public:

    Session(const std::string &path);//CTR
    Session(const Session &session);//copy constructor
    Session &operator=(const Session &session);//copy assignment
    virtual ~Session();             //destructor
    Session(Session &&session);    //MOVE constructor
    Session &operator=(Session &&session);//MOVE assignment

    void simulate();

    void addAgent(const Agent &agent);

    void setGraph(const Graph &graph);

    Graph &getGraph();

    void enqueueInfected(int nodeInd);

    int dequeueInfected();

    TreeType getTreeType() const;

    const std::vector<bool> &getViruses();

    void setNewVirus(int newVirusInd);

    int getCycle() const;


private:
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;
    std::queue<int> infectedQueue;
    std::vector<bool> viruses;
    int cycle;

    void clear();

    bool terminate();

    void checkType(string &type);

    void output();
};

#endif
