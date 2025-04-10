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
            std::cout << "Apu: ����������� " << cash << " �������� �� ����.\n";
            cash = 0;
        }
        catch (const BankOperationError& e) 
        {
            std::cout << "Apu: ������ �������� -> " << e.what() << "\n";
        }
    }

    try 
    {
        bank->SendMoney(bankAccountId, burns.bankAccountId, ELECTRICITY_COST);
        std::cout << "Apu: �������� �� ������������� " << ELECTRICITY_COST << ", �������� �� Burns.\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "Apu: ������ ������ ������������� -> " << e.what() << "\n";
    }
}