#pragma once
#include "Person.h"

class Bart : public Person 
{
public:
    Bart(Money initialCash, Bank& bank, Person& m_apu);
    void Act() override;
private:
    Person& m_apu;
    const long long ITEM_COST = 2;
};