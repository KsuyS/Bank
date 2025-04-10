#pragma once
#include <string>
#include "Bank.h"

class Person 
{
public:
    std::string name;
    Money cash;
    AccountId bankAccountId;
    Bank* bank;

    Person(const std::string& name, Money initialCash, Bank* bank);
    virtual ~Person() = default;

    Money GetBankBalance() const;
    virtual void Act() = 0;
    virtual void PrintStatus() const;
};