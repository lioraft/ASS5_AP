//
// Created by lior on 1/9/23.
//

#ifndef HW5_CPP_POLITICS_POLITICALSYS_H
#define HW5_CPP_POLITICS_POLITICALSYS_H

#include "RepublicanSocial.h"
#include "RepublicanLeader.h"
#include "DemocratSocial.h"
#include "DemocratLeader.h"
#include "RepublicanParty.h"
#include "DemocratParty.h"
#include "Error.h"

class PoliticalSys {
    // vector of all the politicians in the system. is automatically sorted by adding order
    vector<Politician*> politicians;
    // vector of all the parties in the system. is automatically sorted by adding order
    vector<Party*> parties;

    // private functions:
    void addMembersToNewParty(Party& newPar); // function that adds members to new party
    void addNewPoliticianToParty(Politician &newPol); // function that adds a new politician to existing party
    static bool cmpParties(Party *par1, Party *par2); // function to compare between parties
    // function that takes input for politician and checks validation
    bool isPoliticianValid(string id, string power, string ideology_group, string position_type);
    // function that takes input for party and checks validation
    bool isPartyValid(string name, string ideology_group);
    // add politician to the system
    void addNewPolitician(string first, string last, string id, string power, string ideology_group, string position_type);
    // add party to the system
    void addNewParty(string name, string ideology_group);

public:
    // default constructor
    PoliticalSys() {};
    // constructor that takes in string (path to file)
    PoliticalSys(string filename);
    // function that adds politician to system by taking input from console
    void addPoliticianNoFile();
    // function that adds party to system by taking input from console
    void addPartyNoFile();
    // remove politician from system
    void removePoliticianFromSystem();
    // remove party from system
    void removePartyFromSystem();
    // elections
    void elections();
    // print all politicians in the system
    void printPoliticians();
    // print all parties in the system
    void printParties();
    // print the party with the biggest number of members
    void printBiggestParty();
    // destructor
    ~PoliticalSys();
};

#endif //HW5_CPP_POLITICS_POLITICALSYS_H
