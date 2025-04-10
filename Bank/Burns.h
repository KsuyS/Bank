#pragma once
#include "Person.h"

class Burns : public Person 
{
public:
    Burns(Money initialCash, Bank* bank);
    void Act() override;
    void PaySalaryToHomer(Person& homer, Money salary);
};