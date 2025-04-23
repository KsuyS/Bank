#pragma once
#include "Person.h"
#include "Burns.h"

class Homer : public Person
{
public:
    Homer(Money initialCash, Bank& bank, Person& m_marge, Person& m_bart, Person& m_lisa, Person& m_burns);
    void Act() override;
    void TransferToWife();
    void WithdrawForChildren();
    void PayElectricity();
    void DepositRemainingCash();
private:
    Person& m_marge;
    Person& m_bart;
    Person& m_lisa;
    Person& m_burns;
    const long long HUSBAND_TO_WIFE_TRANSFER = 100;
    const long long CHILDREN_ALLOWANCE = 20;
    const long long ELECTRICITY_COST = 100;
};
