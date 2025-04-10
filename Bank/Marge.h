#pragma once
#include "Person.h"

class Marge : public Person 
{
public:
    Person& apu;
    Marge(Money initialCash, Bank* bank, Person& apu);
    void Act() override;
};