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
#include "Helpers.h"

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