#include "Apu.h"
#include <iostream>

Apu::Apu(Money initialCash, Bank& bank, Person& burns) : Person("Apu", initialCash, bank), m_burns(burns) {}

void Apu::Act()
{
    if (GetCash() > 0)
    {
        try
        {
            GetBank().DepositMoney(GetBankAccountId(), GetCash());
            std::cout << "Апу: внёс " << GetCash() << " на счет.\n";
            ClearCash();
        }
        catch (const BankOperationError& e)
        {
            std::cout << "Апу: ошибка депозита " << e.what() << "\n";
        }
    }

    if (GetBank().TrySendMoney(GetBankAccountId(), m_burns.GetBankAccountId(), ELECTRICITY_COST))
    {
        std::cout << "Апу: заплатил за электричество " << ELECTRICITY_COST << ", переведя их Бернсу.\n";
    }
    else 
    {
        std::cout << "Апу: не удалось оплатить электричество.\n";
    }
}