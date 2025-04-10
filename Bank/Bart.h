#pragma once
#include "Person.h"

class Bart : public Person 
{
public:
    Person& apu;
    Bart(Money initialCash, Bank* bank, Person& apu);
    void Act() override;
};