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
    if (GetBank().TrySendMoney(GetBankAccountId(), m_marge.GetBankAccountId(), HUSBAND_TO_WIFE_TRANSFER))
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
    if (GetBank().TryWithdrawMoney(GetBankAccountId(), CHILDREN_ALLOWANCE))
    {
        m_bart.SetCash(m_bart.GetCash() + CHILDREN_ALLOWANCE / 2);
        m_lisa.SetCash(m_lisa.GetCash() + CHILDREN_ALLOWANCE / 2);
        std::cout << "�����: ���� " << CHILDREN_ALLOWANCE << " ��� ����� (�� " << (CHILDREN_ALLOWANCE / 2) << " �������).\n";
    }
    else
    {
        std::cout << "�����: �� ������� ����� �������� ��� �����.\n";
    }
}

void Homer::PayElectricity()
{
    if (GetBank().TrySendMoney(GetBankAccountId(), m_burns.GetBankAccountId(), ELECTRICITY_COST))
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
    if (GetCash() > 0)
    {
        try
        {
            GetBank().DepositMoney(GetBankAccountId(), GetCash());
            std::cout << "�����: ������� ���������� " << GetCash() << " �� ����.\n";
            SetCash(0);
        }
        catch (const BankOperationError& e)
        {
            std::cout << "�����: ������ �������� -> " << e.what() << "\n";
        }
    }
}