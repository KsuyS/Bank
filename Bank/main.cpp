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
    homer.PrintStatus();
    marge.PrintStatus();
    bart.PrintStatus();
    lisa.PrintStatus();
    apu.PrintStatus();
    burns.PrintStatus();
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Bank bank(INITIAL_BANK_CASH);
    Burns burns(BURNS_CASH, &bank);
    Apu apu(APU_CASH, &bank, burns);
    Marge marge(MARGE_CASH, &bank, apu);
    Bart bart(BART_CASH, &bank, apu);
    Lisa lisa(LISA_CASH, &bank, apu);
    Homer homer(HOMER_CASH, &bank, marge, bart, lisa, burns);

    PrintState("Начальные данные:", bank, homer, marge, bart, lisa, apu, burns);

    int iterations;
    std::cout << "Введите количество итераций: ";
    std::cin >> iterations;

    for (int i = 1; i <= iterations; ++i) 
    {
        std::cout << "\nИтерация " << i << "\n";
        homer.Act();
        marge.Act();
        bart.Act();
        lisa.Act();
        apu.Act();
        burns.Act();
        std::cout << "\n";
        PrintState("После итерации: ", bank, homer, marge, bart, lisa, apu, burns);
    }
    return 0;
}