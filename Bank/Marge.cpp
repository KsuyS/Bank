#include "Marge.h"
#include "Constants.h"
#include <iostream>

Marge::Marge(Money initialCash, Bank& bank, Person& apu) : Person("Marge", initialCash, bank), m_apu(apu) {}

void Marge::Act()
{
    if (bank.TrySendMoney(bankAccountId, m_apu.bankAccountId, FOOD_PAYMENT)) 
    {
        std::cout << "Мардж: перевела " << FOOD_PAYMENT << " Апу за продукты.\n";
    }
    else 
    {
        std::cout << "Мардж: не удалось перевести деньги за продукты.\n";
    }
}