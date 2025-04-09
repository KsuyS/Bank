#include "BartLisa.h"
#include <iostream>

BartLisa::BartLisa(std::string name, Bank& bank, AccountId apuAcc)
    : Person(name, 5, bank), apuAccount(apuAcc) {}

void BartLisa::Act() {
    if (cash >= 2) {
        cash -= 2;
        std::cout << name << " купил(а) что-то у Apu за $2\n";
    }
}