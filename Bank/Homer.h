#pragma once
#include "Person.h"
#include "Burns.h"

class Homer : public Person 
{
public:
    Person& marge;
    Person& bart;
    Person& lisa;
    Burns& burns;
    Homer(Money initialCash, Bank* bank, Person& marge, Person& bart, Person& lisa, Burns& burns);
    void Act() override;
};