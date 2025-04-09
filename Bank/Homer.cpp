#include "Homer.h"
#include <iostream>

Homer::Homer(Bank& bank, AccountId margeAcc, AccountId burnsAcc)
    : Person("Homer", 250, bank), margeAccount(margeAcc), burnsAccount(burnsAcc) {}

void Homer::Act() {
    Money salary = 100;

    // Получает зарплату от Бернса
    if (bank.TrySendMoney(burnsAccount, bankAccount, salary)) {
        std::cout << "Homer получил зарплату $" << salary << " от Burns\n";
    }

    // Переводит деньги Мардж
    Money giveToMarge = 30;
    if (bank.TrySendMoney(bankAccount, margeAccount, giveToMarge)) {
        std::cout << "Homer перевел $" << giveToMarge << " Marge\n";
    }

    // Оплачивает электричество
    Money electricityBill = 20;
    if (bank.TrySendMoney(bankAccount, burnsAccount, electricityBill)) {
        std::cout << "Homer заплатил $" << electricityBill << " за электричество\n";
    }

    // Снимает наличные на карманные расходы детям
    Money cashWithdraw = 10;
    if (bank.TryWithdrawMoney(bankAccount, cashWithdraw)) {
        cash += cashWithdraw;
        std::cout << "Homer снял $" << cashWithdraw << " наличными\n";
    }
}