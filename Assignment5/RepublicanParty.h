//
// Created by lior on 1/6/23.
//

#ifndef HW5_CPP_POLITICS_REPUBLICANPARTY_H
#define HW5_CPP_POLITICS_REPUBLICANPARTY_H

#include "Party.h"


class RepublicanParty: public Party {
public:
    // constructor
    RepublicanParty(string name): Party(name){};
    // print republican party - override function in party
    void printParty();
    // destructor
    virtual ~RepublicanParty(){m_chairman = nullptr;};
    // function that returns if a politician can join this party
    virtual bool politicianCanJoin(Politician& other) {return other.canJoinRepublicanParties();};
};


#endif //HW5_CPP_POLITICS_REPUBLICANPARTY_H
