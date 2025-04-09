#include "Apu.h"
#include <iostream>

Apu::Apu(Bank& bank, AccountId burnsAcc)
    : Person("Apu", 20, bank), burnsAccount(burnsAcc) {}

void Apu::Act() {
    Money electricityBill = 15;
    if (bank.TrySendMoney(bankAccount, burnsAccount, electricityBill)) {
        std::cout << "Apu заплатил за электричество $" << electricityBill << "\n";
    }

    if (cash > 10) {
        DepositAllCash();
        std::cout << "Apu положил наличные на счет\n";
    }
}