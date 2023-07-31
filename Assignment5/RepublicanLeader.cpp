//
// Created by lior on 1/6/23.
//

#include "RepublicanLeader.h"

// print politician function
void RepublicanLeader::printPolitician() {
    string chairman;
    if (m_chairman == nullptr)
        chairman = "None";
    else
        chairman = m_chairman->getFirstName();
    cout << "Republican Person:" << m_firstname << " " << m_lastname << ", Id:" << m_id << ", Power:" << m_power << ", Type:L, Chairman: " << chairman << endl;
}