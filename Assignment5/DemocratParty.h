//
// Created by lior on 1/6/23.
//

#ifndef HW5_CPP_POLITICS_DEMOCRATPARTY_H
#define HW5_CPP_POLITICS_DEMOCRATPARTY_H

#include "Party.h"

class DemocratParty: public Party{
public:
    // constructor
    DemocratParty(string name): Party(name){};
    // print democrat party - override function in party
    virtual void printParty();
    // destructor
    virtual ~DemocratParty() {m_chairman = nullptr;};
    // function that returns if a politician can join this party
    virtual bool politicianCanJoin(Politician& other) {return other.canJoinDemocratParties();};
};


#endif //HW5_CPP_POLITICS_DEMOCRATPARTY_H
