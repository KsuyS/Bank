#include "Apu.h"
#include "Constants.h"
#include <iostream>

Apu::Apu(Money initialCash, Bank* bank, Burns& burns)
    : Person("Apu", initialCash, bank), burns(burns) {}

void Apu::Act() 
{
    if (cash > 0) 
    {
        try 
        {
            bank->DepositMoney(bankAccountId, cash);
            std::cout << "Apu: депонировал " << cash << " наличных на счет.\n";
            cash = 0;
        }
        catch (const BankOperationError& e) 
        {
            std::cout << "Apu: ошибка депозита -> " << e.what() << "\n";
        }
    }

    try 
    {
        bank->SendMoney(bankAccountId, burns.bankAccountId, ELECTRICITY_COST);
        std::cout << "Apu: заплатил за электричество " << ELECTRICITY_COST << ", переведя их Burns.\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "Apu: ошибка оплаты электричества -> " << e.what() << "\n";
    }
}