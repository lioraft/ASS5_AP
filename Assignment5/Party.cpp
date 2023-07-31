//
// Created by lior on 1/4/23.
//

#include "Party.h"

// function that takes in reference of a politician, and adds it to politician vector if possible. if succeed to add, returns
// true. else, returns false.
bool Party::addPolitician(Politician *other) {
    // if pointer is null, return false
    if (other == nullptr)
        return false;
    if (politicianCanJoin(*other)) {
        // add to vector of politicians
        m_politicians.push_back(other);
        // change chairman and party pointers
        other->replaceChairman(m_chairman);
        other->replaceParty(this);
        // if succeeded, returns true
        return true;
    }
    else {
        // if can't join
        return false;
    }
}

// function that takes in id of a politician and removes it from politicians vector
bool Party::removePolitician(string id) {
    // create iterator to go through all politicians in the vector
    auto iter = m_politicians.begin();
    // loop until reaches end of politicians vector. when finds, delete it
    while (iter != m_politicians.end()) {
        // if finds
        if ((*iter)->getID() == id) {
            // if is chairman, set as nullpointer
            if (m_chairman != nullptr && (m_chairman->getID() == id)) {
                m_chairman = nullptr;
                // notify all politicians that chairman has left
                notifyChairman(m_chairman);
            }
            // change chairman and party pointers to null
            (*iter)->replaceChairman(nullptr);
            (*iter)->replaceParty(nullptr);
            // delete
            m_politicians.erase(iter);
            // return true
            return true;
        }
        else
            iter++;
    }
    // if not found, return false
    return false;
}

// this function is implementing the observer design pattern. it's a function that elects the
// chairman, and notifies all the politicians in the party by modifying their chairman field through the
// "replace chairman" function.
void Party::primaries() {
    // if no politicians, return
    if (m_politicians.empty())
        return;
    // if currently there is no chairman, set it as the first leader in the vector
    // create iterator to go through all politicians in the vector
    auto iter = m_politicians.begin();
    // loop until reaches end of vector
    while (iter != m_politicians.end()) {
        // if potential runner for chairman role
        if ((*iter)->canBeChairman()) {
            // if power of next leader is bigger than power of current leader, replace the chairman
            if (m_chairman == nullptr || (*iter)->getPowerDuringElections() > m_chairman->getPowerDuringElections()) {
                m_chairman = *iter;
            }
        }
        // advance index
        iter++;
    }
    // after iterating all leaders, update the politicians of the party with the result
    notifyChairman(m_chairman);
}

// this function is implementing the observer design pattern. it's called by the primaries function to notify all
// the members of the party that a new chairman was elected
void Party::notifyChairman(Politician* chairman) {
    // create iterator to go through all politicians in the vector
    auto iter = m_politicians.begin();
    // loop until reaches end of politicians vector. when finds, delete it
    while (iter != m_politicians.end()) {
        // update and advance
        (*iter)->replaceChairman(m_chairman);
        iter++;
    }
}

// function that sums the power of its members during election and returns it
int Party::powerDuringElections() {
    int power = 0;
    // create iterator to go through all politicians in the vector
    auto iter = m_politicians.begin();
    // loop until reaches end of politicians vector. when finds, delete it
    while (iter != m_politicians.end()) {
        // update power and advance
        power+=(*iter)->getPowerDuringElections();
        iter++;
    }
    return power;
}

// a helper function that prints all the members in the party by iterating the politician vector
void Party::printMembersOnly() {
    // create iterator to go through all politicians in the vector
    auto iter = m_politicians.begin();
    // loop until reaches end of politicians vector and print all politicians
    while (iter != m_politicians.end()) {
        cout << "\t";
        (*iter)->printPolitician();
        iter++;
    }
}