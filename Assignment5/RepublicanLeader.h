//
// Created by lior on 1/6/23.
//

#ifndef HW5_CPP_POLITICS_REPUBLICANLEADER_H
#define HW5_CPP_POLITICS_REPUBLICANLEADER_H


#include "Politician.h"
#include <string>
using namespace std;

class RepublicanLeader: public Politician {
public:
    // constructor
    RepublicanLeader(string first_name, string last_name, string id, int power): Politician(first_name, last_name, id, power) {};
    // print function
    virtual void printPolitician();
    // destructor
    virtual ~RepublicanLeader() {m_party = nullptr; m_chairman = nullptr;};
    // function that returns power during elections
    virtual int getPowerDuringElections() {return m_power;};
    // functions related to behavior of class objects
    virtual bool canJoinRepublicanParties() {return true;};
    virtual bool canJoinDemocratParties() {return false;};
    virtual bool canBeChairman(){return true;};
};



#endif //HW5_CPP_POLITICS_REPUBLICANLEADER_H
