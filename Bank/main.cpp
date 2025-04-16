// избавиться от мьютекса
#include <iostream>
#include <windows.h> 
#include "Constants.h"
#include "Bank.h"
#include "Homer.h"
#include "Marge.h"
#include "Bart.h"
#include "Lisa.h"
#include "Apu.h"
#include "Burns.h"

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

void RunSimulation(int iterations, Bank& bank, Homer& homer, Marge& marge, Bart& bart, Lisa& lisa, Apu& apu, Burns& burns)
{
    for (int i = 1; i <= iterations; ++i) 
    {
        std::cout << "\nИтерация " << i << "\n";
        homer.Act();
        marge.Act();
        bart.Act();
        lisa.Act();
        apu.Act();
        burns.Act();
        PrintState("После итерации:", bank, homer, marge, bart, lisa, apu, burns);
    }
}

Money GetOverallInitialTotal() {
    // These constants are defined in Constants.h
    return INITIAL_BANK_CASH + HOMER_CASH + MARGE_CASH + BART_CASH + LISA_CASH + APU_CASH + BURNS_CASH;
}

void CheckBankSystemConsistency(Bank& bank, const Homer& homer, const Marge& marge,
    const Bart& bart, const Lisa& lisa, const Apu& apu, const Burns& burns)
{
    // Считаем наличные деньги, которые есть у персонажей.
    Money personsCash = homer.cash + marge.cash + bart.cash + lisa.cash + apu.cash + burns.cash;

    // Получаем наличные деньги, зарегистрированные в банке.
    Money bankCash = bank.GetCash();

    // Суммируем деньги на счетах каждого участника.
    Money accountsTotal = bank.GetAccountBalance(homer.bankAccountId) +
        bank.GetAccountBalance(marge.bankAccountId) +
        bank.GetAccountBalance(bart.bankAccountId) +
        bank.GetAccountBalance(lisa.bankAccountId) +
        bank.GetAccountBalance(apu.bankAccountId) +
        bank.GetAccountBalance(burns.bankAccountId);

    // Общая сумма денег в системе складывается из наличных денег,
    // зарегистрированных в банке, денежных средств в кошельках участников 
    // и безналичных денег на счетах.
    Money overallTotal = personsCash + bankCash + accountsTotal;

    // Ожидаемая общая сумма – сумма денег, которая изначально была положена в систему.
    Money expectedTotal = GetOverallInitialTotal();

    std::cout << "\n=== Финальное состояние системы ===\n";
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
        std::cout << "Ошибка: наличные деньги участников (" << personsCash
            << ") не равны наличным деньгам в банке (" << bankCash << ").\n";
    }

    if (overallTotal == expectedTotal)
    {
        std::cout << "Проверка: общая сумма денег соответствует ожидаемой.\n";
    }
    else
    {
        std::cout << "Ошибка: общая сумма денег (" << overallTotal
            << ") не соответствует ожидаемой (" << expectedTotal << ").\n";
    }
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int iterations = GetIterations(argc, argv);
    Bank bank(INITIAL_BANK_CASH);
    Burns burns(BURNS_CASH, bank);
    Apu apu(APU_CASH, bank, burns);
    Marge marge(MARGE_CASH, bank, apu);
    Bart bart(BART_CASH, bank, apu);
    Lisa lisa(LISA_CASH, bank, apu);
    Homer homer(HOMER_CASH, bank, marge, bart, lisa, burns);
    burns.SetHomer(homer);

    PrintState("Начальные данные:", bank, homer, marge, bart, lisa, apu, burns);
    RunSimulation(iterations, bank, homer, marge, bart, lisa, apu, burns);
    CheckBankSystemConsistency(bank, homer, marge, bart, lisa, apu, burns);

    return 0;
}