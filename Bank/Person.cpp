#include "Person.h"
#include <iostream>

Person::Person(const std::string& name, Money initialCash, Bank& bank): m_name(name), m_cash(initialCash), m_bank(bank) 
{
    m_bankAccountId = bank.OpenAccount();
}

Money Person::GetBankBalance() const 
{
    return m_bank.GetAccountBalance(m_bankAccountId);
}

void Person::PrintStatus() const 
{
    std::cout << m_name << " - Наличные: " << m_cash
        << ", Счет: " << GetBankBalance() << "\n";
}

std::string Person::GetName() const
{
    return m_name;
}

Money Person::GetCash() const
{
    return m_cash;
}

void Person::AddCash(Money amount)
{
    m_cash += amount;
}

void Person::ClearCash()
{
    m_cash = 0;
}

AccountId Person::GetBankAccountId() const
{
    return m_bankAccountId;
}

Bank& Person::GetBank() const
{
    return m_bank;
}