#pragma once
#include "Person.h"

class Marge : public Person 
{
public:
    Marge(Money initialCash, Bank& bank, Person& m_apu);
    void Act() override;
private:
    Person& m_apu;
    const long long FOOD_PAYMENT = 60;
};