#pragma once
#include "Person.h"
#include "Burns.h"

class Apu : public Person 
{
public:
    Burns& burns;
    Apu(Money initialCash, Bank* bank, Burns& burns);
    void Act() override;
};