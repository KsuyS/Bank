#pragma once
#include <string>
#include "Bank.h"

class Person
{
public:
    Person(const std::string& m_name, Money initialCash, Bank& m_bank);
    virtual ~Person() = default;

    std::string GetName() const;
    Money GetCash() const; 
    //void SetCash(Money newCash); // AddCash (clear cash)
    void AddCash(Money amount);
    void ClearCash();
    AccountId GetBankAccountId() const;
    Bank& GetBank() const;

    Money GetBankBalance() const;
    virtual void Act() = 0;
    virtual void PrintStatus() const;

private:
    std::string m_name;
    Money m_cash;
    AccountId m_bankAccountId;
    Bank& m_bank;
};