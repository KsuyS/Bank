#include "Bank.h"
#include "Homer.h"
#include "Marge.h"
#include "BartLisa.h"
#include "Apu.h"
#include "Burns.h"
#include <iostream>
#include <vector>
#include <memory>
#include <windows.h> 

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int numIterations = 10;
    if (argc > 1) {
        numIterations = std::stoi(argv[1]);
    }

    Bank bank(500);

    AccountId homerAcc = bank.OpenAccount();
    AccountId margeAcc = bank.OpenAccount();
    AccountId apuAcc = bank.OpenAccount();
    AccountId burnsAcc = bank.OpenAccount();

    std::vector<std::unique_ptr<Person>> people;
    people.push_back(std::make_unique<Homer>(bank, margeAcc, burnsAcc));
    people.push_back(std::make_unique<Marge>(bank, apuAcc));
    people.push_back(std::make_unique<BartLisa>("Bart", bank, apuAcc));
    people.push_back(std::make_unique<BartLisa>("Lisa", bank, apuAcc));
    people.push_back(std::make_unique<Apu>(bank, burnsAcc));
    people.push_back(std::make_unique<Burns>(bank));

    for (int i = 0; i < numIterations; ++i) {
        std::cout << "\n=== Итерация " << i + 1 << " ===\n";
        for (auto& person : people) {
            person->Act();
        }
    }

    std::cout << "\n=== Итоги ===\n";
    for (const auto& person : people) {
        person->PrintStatus();
    }

    std::cout << "Наличные в банке: $" << bank.GetCash() << "\n";
}