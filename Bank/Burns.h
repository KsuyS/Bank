#pragma once
#include "Person.h"
#include "Homer.h"

class Burns : public Person
{
public:
    Burns(Money initialCash, Bank& bank);
    void SetHomer(Person& homer);
    void Act() override;
private:
    Person* m_homer = nullptr;
    const long long HOMER_SALARY = 50;
};