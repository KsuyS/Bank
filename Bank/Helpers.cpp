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
        std::cout << "Введите количество итераций: ";
        std::cin >> iterations;
        if (iterations <= 0)
        {
            std::cout << "Ошибка: количество итераций должно быть положительным\n";
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

    std::cout << "\nФинальное состояние системы:\n";
    std::cout << "Наличные денег у персонажей: " << personsCash << "\n";
    std::cout << "Наличные деньги в банке: " << bankCash << "\n";
    std::cout << "Сумма на счетах: " << accountsTotal << "\n";
    std::cout << "Общая сумма денег: " << overallTotal << "\n";
    std::cout << "Ожидаемая сумма денег: " << expectedTotal << "\n\n";

    if (personsCash == bankCash)
    {
        std::cout << "Проверка: наличные деньги у персонажей совпадают с наличными деньгами в банке.\n";
    }
    else
    {
        std::cout << "Ошибка: наличные деньги участников (" << personsCash << ") не равны наличным деньгам в банке (" << bankCash << ").\n";
    }

    if (overallTotal == expectedTotal)
    {
        std::cout << "Проверка: общая сумма денег соответствует ожидаемой.\n";
    }
    else
    {
        std::cout << "Ошибка: общая сумма денег (" << overallTotal << ") не соответствует ожидаемой (" << expectedTotal << ").\n";
    }
}