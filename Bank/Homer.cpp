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
    if (GetBank().TrySendMoney(GetBankAccountId(), m_marge.GetBankAccountId(), HUSBAND_TO_WIFE_TRANSFER))
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
    if (GetBank().TryWithdrawMoney(GetBankAccountId(), CHILDREN_ALLOWANCE))
    {
        m_bart.SetCash(m_bart.GetCash() + CHILDREN_ALLOWANCE / 2);
        m_lisa.SetCash(m_lisa.GetCash() + CHILDREN_ALLOWANCE / 2);
        std::cout << "Гомер: снял " << CHILDREN_ALLOWANCE << " для детей (по " << (CHILDREN_ALLOWANCE / 2) << " каждому).\n";
    }
    else
    {
        std::cout << "Гомер: не удалось снять наличные для детей.\n";
    }
}

void Homer::PayElectricity()
{
    if (GetBank().TrySendMoney(GetBankAccountId(), m_burns.GetBankAccountId(), ELECTRICITY_COST))
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
    if (GetCash() > 0)
    {
        try
        {
            GetBank().DepositMoney(GetBankAccountId(), GetCash());
            std::cout << "Гомер: положил оставшиеся " << GetCash() << " на счёт.\n";
            SetCash(0);
        }
        catch (const BankOperationError& e)
        {
            std::cout << "Гомер: ошибка депозита -> " << e.what() << "\n";
        }
    }
}