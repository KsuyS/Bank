#pragma once
#include "Person.h"

class Lisa : public Person 
{
public:
    Person& apu;
    Lisa(Money initialCash, Bank* bank, Person& apu);
    void Act() override;
};