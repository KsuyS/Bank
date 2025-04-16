// упростить логику Act()

#include "Homer.h"
#include "Constants.h"
#include <iostream>

Homer::Homer(Money initialCash, Bank& bank, Person& marge, Person& bart, Person& lisa, Person& burns)
    : Person("Homer", initialCash, bank), m_marge(marge), m_bart(bart), m_lisa(lisa), m_burns(burns) {}

void Homer::Act()
{
    TransferToWife();
    WithdrawForChildren();
    PayElectricity();
    DepositRemainingCash();
}

void Homer::TransferToWife()
{
    if (bank.TrySendMoney(bankAccountId, m_marge.bankAccountId, HUSBAND_TO_WIFE_TRANSFER))
    {
        std::cout << "Гомер: перевел " << HUSBAND_TO_WIFE_TRANSFER << " жене (Мардж).\n";
    }
    else
    {
        std::cout << "Гомер: не удалось перевести деньги жене.\n";
    }
}

void Homer::WithdrawForChildren()
{
    if (bank.TryWithdrawMoney(bankAccountId, CHILDREN_ALLOWANCE))
    {
        m_bart.cash += CHILDREN_ALLOWANCE / 2;
        m_lisa.cash += CHILDREN_ALLOWANCE / 2;
        std::cout << "Гомер: снял " << CHILDREN_ALLOWANCE << " для детей (по " << (CHILDREN_ALLOWANCE / 2) << " каждому).\n";
    }
    else
    {
        std::cout << "Гомер: не удалось снять наличные для детей.\n";
    }
}

void Homer::PayElectricity()
{
    if (bank.TrySendMoney(bankAccountId, m_burns.bankAccountId, ELECTRICITY_COST))
    {
        std::cout << "Гомер: оплатил электричество " << ELECTRICITY_COST << ", переведя их Бернсу.\n";
    }
    else
    {
        std::cout << "Гомер: не удалось оплатить электричество.\n";
    }
}

void Homer::DepositRemainingCash()
{
    if (cash > 0)
    {
        try
        {
            bank.DepositMoney(bankAccountId, cash);
            std::cout << "Гомер: положил оставшиеся " << cash << " на счёт.\n";
            cash = 0;
        }
        catch (const BankOperationError& e)
        {
            std::cout << "Гомер: ошибка депозита -> " << e.what() << "\n";
        }
    }
}