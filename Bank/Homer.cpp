// ��������� ������ Act()

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
        std::cout << "�����: ������� " << HUSBAND_TO_WIFE_TRANSFER << " ���� (�����).\n";
    }
    else
    {
        std::cout << "�����: �� ������� ��������� ������ ����.\n";
    }
}

void Homer::WithdrawForChildren()
{
    if (bank.TryWithdrawMoney(bankAccountId, CHILDREN_ALLOWANCE))
    {
        m_bart.cash += CHILDREN_ALLOWANCE / 2;
        m_lisa.cash += CHILDREN_ALLOWANCE / 2;
        std::cout << "�����: ���� " << CHILDREN_ALLOWANCE << " ��� ����� (�� " << (CHILDREN_ALLOWANCE / 2) << " �������).\n";
    }
    else
    {
        std::cout << "�����: �� ������� ����� �������� ��� �����.\n";
    }
}

void Homer::PayElectricity()
{
    if (bank.TrySendMoney(bankAccountId, m_burns.bankAccountId, ELECTRICITY_COST))
    {
        std::cout << "�����: ������� ������������� " << ELECTRICITY_COST << ", �������� �� ������.\n";
    }
    else
    {
        std::cout << "�����: �� ������� �������� �������������.\n";
    }
}

void Homer::DepositRemainingCash()
{
    if (cash > 0)
    {
        try
        {
            bank.DepositMoney(bankAccountId, cash);
            std::cout << "�����: ������� ���������� " << cash << " �� ����.\n";
            cash = 0;
        }
        catch (const BankOperationError& e)
        {
            std::cout << "�����: ������ �������� -> " << e.what() << "\n";
        }
    }
}