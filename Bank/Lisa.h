#pragma once
#include "Person.h"

class Lisa : public Person 
{
public:
    Lisa(Money initialCash, Bank& bank, Person& m_apu);
    void Act() override;
private:
    Person& m_apu;
};