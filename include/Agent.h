#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"
#include "Tree.h"


class Agent {
public:
    Agent();

    virtual void act(Session &session) = 0;
    virtual ~Agent()=default;                           //DESTRUCTOR
    virtual Agent *clone() const = 0;
};

class ContactTracer : public Agent {
public:
    ContactTracer();//DEFAULT CONSTRUCTOR
    virtual ~ContactTracer()=default;                           //DESTRUCTOR
    virtual void act(Session &session);

private:
    virtual Agent *clone() const;
};


class Virus : public Agent {
public:
    Virus(int nodeInd);//DEFAULT CONSTRUCTOR
    virtual ~Virus()=default;                           //DESTRUCTOR
    virtual void act(Session &session);

private:
    const int nodeInd;

    virtual Agent *clone() const;
};

#endif
