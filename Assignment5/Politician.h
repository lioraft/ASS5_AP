//
// Created by lior on 1/4/23.
//

#ifndef HW5_CPP_POLITICS_POLITICIAN_H
#define HW5_CPP_POLITICS_POLITICIAN_H

#include <string>
using namespace std;
#include "Party.h"

// letting the compiler know that party is a class
class Party;

class Politician {
protected:
    string m_firstname;
    string m_lastname;
    string m_id;
    Party *m_party; // the politician's party
    Politician *m_chairman; // chairman of party
    int m_power;
public:
    // constructor
    Politician(string first_name, string last_name, string id, int power);
    // replace chairman - function that takes in a pointer of a chairman, and updates it
    void replaceChairman(Politician *chairman) {m_chairman = chairman;};
    // replace party - function that takes in pointer of a party, and updates it
    void replaceParty(Party *party) {m_party = party;};
    // get id
    string getID() {return m_id;};
    // get first name
    string getFirstName() {return m_firstname;};
    // get party
    Party* getParty() {return m_party;};
    // destructor
    virtual ~Politician() {};

    //pure virtual function, making politician an interface
    // print function
    virtual void printPolitician()=0;
    // get power during elections
    virtual int getPowerDuringElections()=0;
    // functions that return if a politician can join certain parties
    virtual bool canJoinRepublicanParties() = 0;
    virtual bool canJoinDemocratParties() = 0;
    // functions that return if a politician is potential runner for chairman role
    virtual bool canBeChairman()=0;

};


#endif //HW5_CPP_POLITICS_POLITICIAN_H
