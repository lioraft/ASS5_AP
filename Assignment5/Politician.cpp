//
// Created by lior on 1/4/23.
//

#include <string>
#include "Politician.h"

// constructor that takes in first name, last name, id, and power.
// constructor initializes politician object with these elements.
Politician::Politician(string first_name, string last_name, string id, int power) {
    // copy strings and set it in the politician
    m_firstname = first_name;
    m_lastname = last_name;
    m_id = id;
    // when first initializes, no party and no chairman
    m_party = nullptr;
    m_chairman = nullptr;
    m_power = power;
}

