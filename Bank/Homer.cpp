// ��������� ������ Act: ������ ��������, ������ ��������� ������ ����, ����� �������� �����, ��������
// ��������������, ����� �������� ������� � ������� ��� �������� �� ����, ������������� ��� Act � ��������� ����������

#include "Homer.h"
#include "Constants.h"
#include <iostream>


Homer::Homer(Money initialCash, Bank& bank, Person& marge, Person& bart, Person& lisa, Burns& burns)
    : Person("Homer", initialCash, bank), m_marge(marge), m_bart(bart), m_lisa(lisa), m_burns(burns) {}

void Homer::Act() 
{
    Money required = HUSBAND_TO_WIFE_TRANSFER + CHILDREN_ALLOWANCE + ELECTRICITY_COST;

    if (bank.GetAccountBalance(bankAccountId) < required) {
        Money diff = required - bank.GetAccountBalance(bankAccountId);
        if (cash >= diff) 
        {
            try 
            {
                bank.DepositMoney(bankAccountId, diff);
                cash -= diff;
                std::cout << "�����: ������� " << diff << " �� ����.\n";
            }
            catch (const BankOperationError& e) 
            {
                std::cout << "�����: ������ �������� -> " << e.what() << "\n";
            }
        }
        else 
        {
            std::cout << "�����: ������������ ������ �������� ��� �������� (��������� " << diff << ", ������� " << cash << ").\n";
        }
    }

    try 
    {
        bank.SendMoney(bankAccountId, m_marge.bankAccountId, HUSBAND_TO_WIFE_TRANSFER);
        std::cout << "�����: ������� " << HUSBAND_TO_WIFE_TRANSFER << " ���� (�����).\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "�����: ������ �������� ���� -> " << e.what() << "\n";
    }

    try 
    {
        bank.WithdrawMoney(bankAccountId, CHILDREN_ALLOWANCE);
        m_bart.cash += CHILDREN_ALLOWANCE / 2;
        m_lisa.cash += CHILDREN_ALLOWANCE / 2;
        std::cout << "�����: ���� " << CHILDREN_ALLOWANCE << " ��� ����� (�� 10 �������).\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "�����: ������ ������ �������� -> " << e.what() << "\n";
    }

    try 
    {
        bank.SendMoney(bankAccountId, m_burns.bankAccountId, ELECTRICITY_COST);
        std::cout << "�����: ������� ������������� " << ELECTRICITY_COST << ", �������� �� ������.\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "�����: ������ ������ ������������� -> " << e.what() << "\n";
    }
}