//
// Created by lior on 1/6/23.
//

#include "DemocratParty.h"

void DemocratParty::printParty() {
    // check if there is a chairman and print name if exists
    string chairman_name;
    if (m_chairman == nullptr)
        chairman_name = "None";
    else
        chairman_name = m_chairman->getFirstName();
    // print details
    cout << "Democrat Party: " << m_name << ", chairman:" << chairman_name << ", Size:" << m_politicians.size() << endl;
    // printing all the members using helper function
    printMembersOnly();
}