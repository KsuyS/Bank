#include "Person.h"
#include <iostream>

Person::Person(std::string name, Money initialCash, Bank& bank)
    : name(std::move(name)), cash(initialCash), bank(bank) {
    bankAccount = bank.OpenAccount();
}

void Person::DepositAllCash() {
    if (cash > 0) {
        bank.DepositMoney(bankAccount, cash);
        cash = 0;
    }
}

void Person::WithdrawFromBank(Money amount) {
    if (bank.TryWithdrawMoney(bankAccount, amount)) {
        cash += amount;
    }
}

void Person::PrintStatus() const {
    std::cout << name << " - Cash: " << cash
        << ", Bank Balance: " << bank.GetAccountBalance(bankAccount) << std::endl;
}