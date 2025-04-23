#include "ConsistencyHelpers.h"
#include <iostream>
#include "Constants.h"

Money GetOverallInitialTotal()
{
    return HOMER_CASH + MARGE_CASH + BART_CASH + LISA_CASH + APU_CASH + BURNS_CASH;
}

void CheckBankSystemConsistency(Bank& bank, const Homer& homer, const Marge& marge,
    const Bart& bart, const Lisa& lisa, const Apu& apu, const Burns& burns)
{
    Money personsCash = homer.GetCash() + marge.GetCash() + bart.GetCash() + lisa.GetCash() + apu.GetCash() + burns.GetCash();
    Money bankCash = bank.GetCash();
    Money accountsTotal = bank.GetAccountBalance(homer.GetBankAccountId()) +
        bank.GetAccountBalance(marge.GetBankAccountId()) +
        bank.GetAccountBalance(bart.GetBankAccountId()) +
        bank.GetAccountBalance(lisa.GetBankAccountId()) +
        bank.GetAccountBalance(apu.GetBankAccountId()) +
        bank.GetAccountBalance(burns.GetBankAccountId());

    Money overallTotal = personsCash + accountsTotal;
    Money expectedTotal = GetOverallInitialTotal();

    std::cout << "\n��������� ��������� �������:\n";
    std::cout << "�������� ����� � ����������: " << personsCash << "\n";
    std::cout << "�������� ������ � �����: " << bankCash << "\n";
    std::cout << "����� �� ������: " << accountsTotal << "\n";
    std::cout << "����� ����� �����: " << overallTotal << "\n";
    std::cout << "��������� ����� �����: " << expectedTotal << "\n\n";

    if (personsCash == bankCash)
    {
        std::cout << "��������: �������� ������ � ���������� ��������� � ��������� �������� � �����.\n";
    }
    else
    {
        std::cout << "������: �������� ������ ���������� (" << personsCash << ") �� ����� �������� ������� � ����� (" << bankCash << ").\n";
    }

    if (overallTotal == expectedTotal)
    {
        std::cout << "��������: ����� ����� ����� ������������� ���������.\n";
    }
    else
    {
        std::cout << "������: ����� ����� ����� (" << overallTotal << ") �� ������������� ��������� (" << expectedTotal << ").\n";
    }
}