#include "Apu.h"
#include "Constants.h"
#include <iostream>

Apu::Apu(Money initialCash, Bank& bank, Person& burns) : Person("Apu", initialCash, bank), m_burns(burns) {}

void Apu::Act()
{
    if (cash > 0)
    {
        try
        {
            bank.DepositMoney(bankAccountId, cash);
            std::cout << "Апу: внёс " << cash << " на счет.\n";
            cash = 0;
        }
        catch (const BankOperationError& e)
        {
            std::cout << "Апу: ошибка депозита " << e.what() << "\n";
        }
    }

    if (bank.TrySendMoney(bankAccountId, m_burns.bankAccountId, ELECTRICITY_COST)) 
    {
        std::cout << "Апу: заплатил за электричество " << ELECTRICITY_COST << ", переведя их Бернсу.\n";
    }
    else 
    {
        std::cout << "Апу: не удалось оплатить электричество.\n";
    }
}