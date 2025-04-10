#include "Apu.h"
#include "Constants.h"
#include <iostream>

Apu::Apu(Money initialCash, Bank* bank, Burns& burns): Person("Apu", initialCash, bank), burns(burns) {}

void Apu::Act() 
{
    if (cash > 0) 
    {
        try 
        {
            bank->DepositMoney(bankAccountId, cash);
            std::cout << "���: ��� " << cash << " �� ����.\n";
            cash = 0;
        }
        catch (const BankOperationError& e) 
        {
            std::cout << "���: ������ �������� -> " << e.what() << "\n";
        }
    }

    try 
    {
        bank->SendMoney(bankAccountId, burns.bankAccountId, ELECTRICITY_COST);
        std::cout << "���: �������� �� ������������� " << ELECTRICITY_COST << ", �������� �� ������.\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "���: ������ ������ ������������� -> " << e.what() << "\n";
    }
}