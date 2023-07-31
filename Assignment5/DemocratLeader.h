//
// Created by lior on 1/6/23.
//

#ifndef HW5_CPP_POLITICS_DEMOCRATLEADER_H
#define HW5_CPP_POLITICS_DEMOCRATLEADER_H


#include "Politician.h"
#include <string>
using namespace std;

class DemocratLeader: public Politician {
public:
    // constructor
    DemocratLeader(string first_name, string last_name, string id, int power): Politician(first_name, last_name, id, power) {};
    // print function
    virtual void printPolitician();
    // destructor
    virtual ~DemocratLeader() {m_party = nullptr; m_chairman = nullptr;};
    // function that returns power during elections
    virtual int getPowerDuringElections() {return m_power;};
    // functions related to behavior of class objects
    virtual bool canJoinRepublicanParties() {return false;};
    virtual bool canJoinDemocratParties() {return true;};
    virtual bool canBeChairman(){return true;};
};


#endif //HW5_CPP_POLITICS_DEMOCRATLEADER_H
