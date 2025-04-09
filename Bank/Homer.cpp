#include "Homer.h"
#include <iostream>

Homer::Homer(Bank& bank, AccountId margeAcc, AccountId burnsAcc)
    : Person("Homer", 250, bank), margeAccount(margeAcc), burnsAccount(burnsAcc) {}

void Homer::Act() {
    Money salary = 100;

    // �������� �������� �� ������
    if (bank.TrySendMoney(burnsAccount, bankAccount, salary)) {
        std::cout << "Homer ������� �������� $" << salary << " �� Burns\n";
    }

    // ��������� ������ �����
    Money giveToMarge = 30;
    if (bank.TrySendMoney(bankAccount, margeAccount, giveToMarge)) {
        std::cout << "Homer ������� $" << giveToMarge << " Marge\n";
    }

    // ���������� �������������
    Money electricityBill = 20;
    if (bank.TrySendMoney(bankAccount, burnsAccount, electricityBill)) {
        std::cout << "Homer �������� $" << electricityBill << " �� �������������\n";
    }

    // ������� �������� �� ��������� ������� �����
    Money cashWithdraw = 10;
    if (bank.TryWithdrawMoney(bankAccount, cashWithdraw)) {
        cash += cashWithdraw;
        std::cout << "Homer ���� $" << cashWithdraw << " ���������\n";
    }
}