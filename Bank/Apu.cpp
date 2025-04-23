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
            std::cout << "���: ��� " << GetCash() << " �� ����.\n";
            ClearCash();
        }
        catch (const BankOperationError& e)
        {
            std::cout << "���: ������ �������� " << e.what() << "\n";
        }
    }

    if (GetBank().TrySendMoney(GetBankAccountId(), m_burns.GetBankAccountId(), ELECTRICITY_COST))
    {
        std::cout << "���: �������� �� ������������� " << ELECTRICITY_COST << ", �������� �� ������.\n";
    }
    else 
    {
        std::cout << "���: �� ������� �������� �������������.\n";
    }
}