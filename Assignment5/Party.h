//
// Created by lior on 1/4/23.
//

#ifndef HW5_CPP_POLITICS_PARTY_H
#define HW5_CPP_POLITICS_PARTY_H

#include <string>
using namespace std;
#include "Politician.h"
#include <vector>
#include <iostream>

// letting the compiler know that politician is a class
class Politician;

class Party {
protected:
    // name of party
    string m_name;
    // pointer to chairman
    Politician* m_chairman;
    // vector of all the politicians
    vector<Politician*> m_politicians;
public:
    // default constructor
    Party() {m_name = ""; m_chairman = nullptr;}
    // constructor
    Party(string name){m_name = name; m_chairman = nullptr;};
    // function that adds politician to party
    virtual bool addPolitician(Politician *other);
    // function that removes politician from party
    bool removePolitician(string id);
    // primaries function - function that elects chairman
    void primaries();
    // function that takes in the chairman elected in primaries and notifies all the politicians he is the new chairman
    void notifyChairman(Politician* chairman);
    // function that calculates the power of the party during elections
    int powerDuringElections();
    // get the size of the party
    int getSize() {return m_politicians.size();};
    // helper function that prints only the members of the party. will be used in print party.
    void printMembersOnly();
    // get name of party
    string getName() {return m_name;};
    // get chairman
    Politician& getChairman() {return *m_chairman;};
    // destructor
    virtual ~Party() {};

    // pure virtual functions, making party an interface
    // print function
    virtual void printParty() = 0;
    // function that takes in reference of a politician and returns if he can join the party
    virtual bool politicianCanJoin(Politician& other) = 0;

    // friend class
    friend class PoliticalSys;
};


#endif //HW5_CPP_POLITICS_PARTY_H
