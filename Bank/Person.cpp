#include "Person.h"
#include <iostream>

Person::Person(const std::string& name, Money initialCash, Bank* bank): name(name), cash(initialCash), bank(bank) 
{
    bankAccountId = bank->OpenAccount();
}

Money Person::GetBankBalance() const 
{
    return bank->GetAccountBalance(bankAccountId);
}

void Person::PrintStatus() const 
{
    std::cout << name << " - ��������: " << cash
        << ", ����: " << GetBankBalance() << "\n";
}