#include "Marge.h"
#include "Constants.h"
#include <iostream>

Marge::Marge(Money initialCash, Bank& bank, Person& apu) : Person("Marge", initialCash, bank), m_apu(apu) {}

void Marge::Act()
{
    if (bank.TrySendMoney(bankAccountId, m_apu.bankAccountId, FOOD_PAYMENT)) 
    {
        std::cout << "�����: �������� " << FOOD_PAYMENT << " ��� �� ��������.\n";
    }
    else 
    {
        std::cout << "�����: �� ������� ��������� ������ �� ��������.\n";
    }
}