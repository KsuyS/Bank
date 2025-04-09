#pragma once

#include "Bank.h"
#include <string>

class Person {
protected:
    std::string name;
    AccountId bankAccount;
    Money cash;
    Bank& bank;

public:
    Person(std::string name, Money initialCash, Bank& bank);
    virtual ~Person() = default;

    virtual void Act() = 0;
    void DepositAllCash();
    void WithdrawFromBank(Money amount);
    void PrintStatus() const;
};