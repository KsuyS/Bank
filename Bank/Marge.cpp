#include "Marge.h"
#include "Constants.h"
#include <iostream>

Marge::Marge(Money initialCash, Bank& bank, Person& apu) : Person("Marge", initialCash, bank), m_apu(apu) {}

void Marge::Act()
{
    if (GetBank().TrySendMoney(GetBankAccountId(), m_apu.GetBankAccountId(), FOOD_PAYMENT))
    {
        std::cout << "�����: �������� " << FOOD_PAYMENT << " ��� �� ��������.\n";
    }
    else 
    {
        std::cout << "�����: �� ������� ��������� ������ �� ��������.\n";
    }
}