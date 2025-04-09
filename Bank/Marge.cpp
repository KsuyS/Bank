#include "Marge.h"
#include <iostream>

Marge::Marge(Bank& bank, AccountId apuAcc)
    : Person("Marge", 100, bank), apuAccount(apuAcc) {}

void Marge::Act() {
    Money groceries = 20;
    if (bank.TrySendMoney(bankAccount, apuAccount, groceries)) {
        std::cout << "Marge купила продукты у Apu за $" << groceries << "\n";
    }
}