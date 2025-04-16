#include "Helpers.h"
#include <iostream>
#include <cstdlib>
#include "Constants.h"

void PrintState(const std::string& message, const Bank& bank, const Homer& homer, const Marge& marge,
    const Bart& bart, const Lisa& lisa, const Apu& apu, const Burns& burns)
{
    std::cout << message << "\n";
    homer.PrintStatus();
    marge.PrintStatus();
    bart.PrintStatus();
    lisa.PrintStatus();
    apu.PrintStatus();
    burns.PrintStatus();
}

int GetIterations(int argc, char* argv[])
{
    int iterations = 0;
    if (argc > 1)
    {
        iterations = atoi(argv[1]);
    }

    if (iterations <= 0)
    {
        std::cout << "������� ���������� ��������: ";
        std::cin >> iterations;
        if (iterations <= 0)
        {
            std::cout << "������: ���������� �������� ������ ���� �������������\n";
            exit(1);
        }
    }
    return iterations;
}

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