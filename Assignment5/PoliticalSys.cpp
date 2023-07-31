//
// Created by lior on 1/9/23.
//

#include <string>
#include "PoliticalSys.h"
#include <algorithm>
#include <fstream>
#include <sstream>

/* ----- constructor -----
 * takes in the name of the file, reads it and convert the information in it to political system.*/
PoliticalSys::PoliticalSys(string filename) {
    // boolean that indicates if current read is of politician or party
    bool isParties = false;
    // create stream and open file
    ifstream config;
    config.open(filename);
    // reads file until it reaches the end of the file
    while (config) {
        // buffer for current line
        string curline;
        // read line by line
        getline(config, curline);
        // if empty string, break
        if (curline.empty())
            break;
        // if not, if there is \r at the end trim it
        else {
            if (curline[curline.length()-1] == '\r')
                curline.erase(curline.length()-1);
        }
        // create string stream from line
        stringstream curlinestream(curline);
        // if reached parties section, change boolean
        if (curline == "Parties:")
            isParties = true;
        // if currently reading politician info
        if (!isParties && curline != "Politicians:") {
            // create strings for input
            string firstname, lastname, id, group, role, power;
            // stream into string variables
            curlinestream >> firstname >> lastname >> id >>power >>group >> role;
            // use add new politician function
            addNewPolitician(firstname, lastname, id, power, group, role);
        }
        // if currently reading party info
        if (isParties && curline != "Parties:")
        {
            // create strings for input
            string name, group;
            // stream into string variables
            curlinestream >> name >> group;
            // use add new party function
            addNewParty(name, group);
        }
    }
    // after finish reading, close the file
    config.close();
}

/* ----- functions for adding a new politician to the system ----- */

// this function takes in a reference to a new politician, and adds it to the most suitable party. it first adds to the first
// party he fits in, and then checks for the smallest party, and if finds, transfer him.
void PoliticalSys::addNewPoliticianToParty(Politician &newPol) {
    //iterator for all parties
    auto partyiter = parties.begin();
    while (partyiter != parties.end()) {
        // if not in party, add to the first party found
        if (newPol.getParty() == nullptr) {
            (*partyiter)->addPolitician(&newPol);
        }
        else {
            // if is in party but his current party is bigger than iterator party, transfer
           if((*partyiter)->getSize() < newPol.getParty()->getSize() && ((*partyiter)->politicianCanJoin(newPol))) {
               newPol.getParty()->removePolitician(newPol.getID());
               (*partyiter)->addPolitician(&newPol);
           }
        }
        partyiter++;
    }
}

// this function takes variables for initializing politician and checks if input is valid. if valid, sends to constructor. else, repeats loop for input
// until it gets valid input.
bool PoliticalSys::isPoliticianValid(string id, string power, string ideology_group, string position_type) {
    // check input is valid
    // if id not number
    for (int i = 0; i < id.length(); i++) {
        if (!isdigit(id[i]))
            return false;
    }
    // if power not number
    for (int i = 0; i < power.length(); i++) {
        if (!isdigit(power[i]))
            return false;
    }
    // if power not positive number
    if (stoi(power) < 0)
        return false;
    // if not right group or position
    if ((ideology_group != "R" && ideology_group != "D") || (position_type != "S" && position_type != "L")) {
        return false;
    }
    // create iterator to go through all politicians in the vector
    auto iter = politicians.begin();
    // loop until reaches end of politicians vector
    while (iter != politicians.end()) {
        if ((*iter)->getID() ==id) {
            // if finds, return false
            return false;
        } else
            iter++;
    }
    // if all input valid, return true
    return true;
}


// function that takes in the data of a new politician, initialize it and adds it to a party using "addNewPoliticianToParty".
void PoliticalSys::addNewPolitician(string first, string last, string id, string power, string ideology_group, string position_type) {
    // create politician. the type is decided by ideology and role type that were entered in input:
    // convert power to integer
    int convertedpower = stoi(power);
    // create pointer to new politician
    Politician *ppol;
    // if republican
    if (ideology_group == "R") {
        // if social
        if (position_type == "S") {
            ppol = new RepublicanSocial(first, last, id, convertedpower);
        }
            // if leader
        else {
            ppol = new RepublicanLeader(first, last, id, convertedpower);
        }
    } else { // if democrat
        // if social
        if (position_type == "S") {
            ppol = new DemocratSocial(first, last, id, convertedpower);
        }
            // if leader
        else {
            ppol = new DemocratLeader(first, last, id, convertedpower);
        }
    }
    // add to a party
    addNewPoliticianToParty(*ppol);
    // add politician to politicians vector
    politicians.push_back(ppol);
}

// this function takes input from user by console and not by file, and initializes a new politician using addnewpolitician function.
void PoliticalSys::addPoliticianNoFile() {
    string first, last, id, power, ideology_group, position_type;
    bool isInputOk = false;
    cout << "---Create Politician---" << endl;
    while (!isInputOk) {
        try {
            // print menu and ask for input
            cout << "First name:" << endl;
            cin >> first;
            cout << "Last name:" << endl;
            cin >> last;
            cout << "ID:" << endl;
            cin >> id;
            cout << "Power:" << endl;
            cin >> power;
            cout << "Republican or Democratic person" << endl;
            cin >> ideology_group;
            cout << "Leader or Social" << endl;
            cin >> position_type;
            // checks if input valid
            isInputOk = isPoliticianValid(id, power, ideology_group, position_type);
            // if not valid throw exception
            if (!isInputOk)
                throw newObjectError();
        }
            // catch error and return to print again
        catch(Error &err) {
            err.Handle();
        }
    }
    // if input valid, add to system
    addNewPolitician(first, last, id, power, ideology_group, position_type);
}

/* ----- functions for adding a new party to the system ----- */

// function that takes in a reference of a new party and transfers existing politicians to it based on their seniority
void PoliticalSys::addMembersToNewParty(Party &newPar) {
    // if no politicians, return
    if (politicians.empty())
        return;
    // iterator to iterate all politician from most senior to newest
        auto pol_iter = politicians.begin();
        // loop until reaches end of politicians vector
        while (pol_iter != politicians.end()) {
            // if politician has no party or new party is smaller than current party
            if ((*pol_iter)->getParty() == nullptr) {
                newPar.addPolitician(*(pol_iter));
            }
            else
                if (newPar.getSize() < (*pol_iter)->getParty()->getSize() && newPar.politicianCanJoin(*(*pol_iter))) {
                    // remove from previous party
                    Party *prev = (*pol_iter)->getParty();
                    string id = (*pol_iter)->getID();
                    prev->removePolitician(id);
                    // add to new party
                    newPar.addPolitician((*pol_iter));
            }
                pol_iter++;
        }
}

// function that takes input for initializing party and reutns if the input is valid
bool PoliticalSys::isPartyValid(string name, string ideology_group) {
    // check input is valid
    if (ideology_group != "R" && ideology_group != "D") {
        // if not valid
        return false;
    }
    // create iterator to go through all parties in the vector
    auto iter = parties.begin();
    // loop until reaches end of parties vector
    while (iter != parties.end()) {
        if ((*iter)->getName() == name) {
            // if finds
            return false;
        } else
            iter++;
    }
    // if input valid, returns true
    return true;
}


// function that takes in the data of a new party, creates it and adds members to it using "addMembersToNewParty" function.
void PoliticalSys::addNewParty(string name, string ideology_group) {
    // create pointer to new party
    Party *newPar;
    // if republican party
    if (ideology_group == "R") {
        newPar = new RepublicanParty(name);
    } else {
        // if democrat party
        newPar  = new DemocratParty(name);
    }
    //add new members
    addMembersToNewParty(*newPar);
    // add to parties vector
    parties.push_back(newPar);
}

// this function takes input from user by console and not by file, and initializes a new party using addNewParty function.
void PoliticalSys::addPartyNoFile() {
    // try take input
    bool isValidInput = false;
    cout << "---Create Party---" << endl;
    string name;
    string ideology_group;
    while (!isValidInput) {
        try {
            // print menu and ask for input
            cout << "Name:" << endl;
            cin >> name;
            cout << "Republican or Democratic party" << endl;
            cin >> ideology_group;
            // check if input is valid
            isValidInput = isPartyValid(name, ideology_group);
            // if not succeeded, throw exception and take input again
            if (!isValidInput)
                throw newObjectError();
        }
        // catch error
        catch(Error &err) {
            err.Handle();
        }
    }
    //if data valid, create party
    addNewParty(name, ideology_group);
}

/* ----- removing objects functions ----- */

// function that takes input id from user and removes the politician from the system, if exist. if not exist, throws exception
void PoliticalSys::removePoliticianFromSystem() {
    // if politicians vector is empty, return to menu
    if (politicians.empty())
        return;
    string id;
    bool isInputOk = false;
    cout << "---Remove Politician---" << endl;
    while (!isInputOk) {
        try {
            // print menu and ask for input
            cout << "Enter the ID:" << endl;
            cin >> id;
            // check input is valid:
            // if positive not number
            for (int i = 0; i < id.length(); i++) {
                if (!isdigit(id[i]))
                    throw removePoliticianError();
            }
            // if id is a valid number, iteate the vector of politicians and search for the politician with this id
            // create iterator
            auto iter = politicians.begin();
            // loop until reaches end of politicians vector
            while (iter != politicians.end()) {
                if ((*iter)->getID() == id) {
                    // if finds, delete from all data structures
                    // remove from party
                    (*iter)->getParty()->removePolitician(id);
                    // delete memory created
                    delete *iter;
                    // remove from politicians vector
                    politicians.erase(iter);
                    // change is input ok
                    isInputOk = true;
                    break;
                } else
                    iter++;
            }
            // if didn't find politician, throw exception
            if (!isInputOk)
                throw removePoliticianError();
        }
        catch (Error &err) {
            err.Handle();
        }
    }
}

// function that takes input id from user and removes the party from the system, if exist. if not exist, throws exception
void PoliticalSys::removePartyFromSystem() {
// if parties vector is empty, return to menu
    if (parties.empty())
        return;
    // print menu and ask for input
    cout << "---Remove Party---" << endl;
    string name;
    bool isInputOk = false;
    while (!isInputOk) {
        try {
    cout << "Enter party name:" << endl;
    cin >> name;
    // iterate the parties and search for the politician with this name
    // create iterator
    auto iter = parties.begin();
    // loop until reaches end of parties vector
    while (iter != parties.end()) {
        // compare by name
        if ((*iter)->getName() == name) {
            // create iterator for all politicians and transfer them to other parties
            vector<Politician*> pol_vec = (*iter)->m_politicians;
            // create iterator for party members
            auto iterforpols = pol_vec.begin();
            while (iterforpols != pol_vec.end()) {
                // change pointers to null
                (*iterforpols)->replaceChairman(nullptr);
                (*iterforpols)->replaceParty(nullptr);
                iterforpols++;
            }
            // delete memory created
            delete *iter;
            // remove from parties vector
            parties.erase(iter);
            // create iterator for adding party members to new parties
            auto iterfornewpars = pol_vec.begin();
            while (iterfornewpars != pol_vec.end()) {
                // add to new party
                addNewPoliticianToParty(*(*iterfornewpars));
                iterfornewpars++;
            }
            // change input to be valid
            isInputOk = true;
            // break out of loop
            break;
        } else
            iter++;
    }
    // if not found, throw remove party exception
    if (!isInputOk)
        throw removePartyError();
        }
        catch (Error &err) {
            err.Handle();
        }
    }
}

// function that runs the elections in three steps: first primaries, then the process of electing the party with the most power,
// and then printing out the results.
void PoliticalSys::elections() {
    // if no parties, return to menu
    if (parties.empty())
        return;
    // first step - primaries:
    cout << "----Primaries----" << endl;
    // create iterator to go through all parties in the vector
    auto iter = parties.begin();
    // loop until reaches end of parties vector
    while (iter != parties.end()) {
        // primaries in every party
        (*iter)->primaries();
        // print out the results
        if ((*iter)->m_chairman != nullptr)
            cout << (*iter)->getChairman().getFirstName() << " is the chairman of " << (*iter)->getName() << endl;
        iter++;
    }

    // second step - elections:
    cout << "----Elections----" << endl;
    // set current winner to first party and then start iterating and comparing
    Party *winner = *(parties.begin());
    // create iterator and start iterating the parties
    // create iterator to go through all parties in the vector
    auto iterforelections = parties.begin();
    // loop until reaches end of parties vector
    while (iterforelections != parties.end()) {
        // if there is stronger party, change pointer of winner
        if ((*iterforelections)->powerDuringElections() > winner->powerDuringElections()) {
            winner = *iterforelections;
        }
        cout << "Party: " << (*iterforelections)->getName() << ",Power: " << (*iterforelections)->powerDuringElections() << endl;
        iterforelections++;
    }

    // third step: results
    cout << "----Elections Results----" << endl;
    if (winner->m_chairman != nullptr)
        cout << winner->getName() << " party won the elections and " << winner->getChairman().getFirstName() << " is the prime minister " << endl;
}

/* ---- functions for printing objects ----- */

// print all politicians in vector
void PoliticalSys::printPoliticians() {
    // if empty, return
    if (politicians.empty())
        return;
    cout << "----Politicians----" << endl;
    // create iterator to go through all politicians in the vector
    auto iter = politicians.begin();
    // loop until reaches end of politicians vector
    while (iter != politicians.end()) {
        // print politician and advance
        (*iter)->printPolitician();
        iter++;
    }
}

// print all parties in vector
void PoliticalSys::printParties() {
    // if empty, return
    if (parties.empty())
        return;
    cout << "----Parties----" << endl;
    // create iterator to go through all parties in the vector
    auto iter = parties.begin();
    // loop until reaches end of parties vector
    while (iter != parties.end()) {
        // print party and advance
        (*iter)->printParty();
        iter++;
    }
}

/* ----- biggest party functions ----- */

// function that takes in pointers of two parties, and compares them by returning which one
// has more members. if there is a tie, it compares the parties' names with strcmp. if par1<par2, returns true.
// if par1>par2, returns false.
bool PoliticalSys::cmpParties(Party *par1, Party *par2) {
    // if sizes are equal, return by strcmp
    if (par1->getSize() == par2->getSize()) {
        // compare with strcmp
        if (par1->getName() < par2->getName()) {
            return true;
        }
        return false;
    }
    // if not equal, return by size comparison
   return par1->getSize() < par2->getSize();
}

// function that prints the biggest party in parties vector
void PoliticalSys::printBiggestParty() {
    // if parties vector is empty, return to menu
    if (parties.empty())
        return;
    cout << "----Biggest Party----" << endl;
    cout << "[" << (*max_element(parties.begin(), parties.end(), cmpParties))->getName() << "," << (*max_element(parties.begin(), parties.end(), cmpParties))->getSize() << "]" << endl;
}

/* ----- destructor ----- */
// deletes all memory created from vectors of politicians and parties
PoliticalSys::~PoliticalSys() {
    // delete all politicians
    for (int i = 0; i < politicians.size(); i++) {
        delete(politicians[i]);
    }
    // delete all parties
    for (int i = 0; i < parties.size(); i++) {
        delete(parties[i]);
    }
}




