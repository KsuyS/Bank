#pragma once
#include "Person.h"
#include "Burns.h"

class Apu : public Person 
{
public:
    Apu(Money initialCash, Bank& bank, Person& m_burns);
    void Act() override;
private:
    Person& m_burns;
};