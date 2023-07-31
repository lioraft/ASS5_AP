//
// Created by lior on 1/6/23.
//

#include "DemocratSocial.h"

// print politician function
void DemocratSocial::printPolitician() {
        string chairman;
        if (m_chairman == nullptr)
            chairman = "None";
        else
            chairman = m_chairman->getFirstName();
    cout << "Democratic Person:" << m_firstname << " " << m_lastname << ", Id:" << m_id << ", Power:" << m_power << ", Type:S, Chairman: " << chairman << endl;
}