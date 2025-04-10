#include "Homer.h"
#include "Constants.h"
#include <iostream>

Homer::Homer(Money initialCash, Bank* bank, Person& marge, Person& bart, Person& lisa, Burns& burns)
    : Person("Homer", initialCash, bank), marge(marge), bart(bart), lisa(lisa), burns(burns) {}

// ��������� ������ Act: ������ ��������, ������ ��������� ������ ����, ����� �������� �����, ��������
// ��������������, ����� �������� ������� � ������� ��� �������� �� ����, ������������� ��� Act � ��������� ����������

void Homer::Act() 
{
    Money required = HUSBAND_TO_WIFE_TRANSFER + CHILDREN_ALLOWANCE + ELECTRICITY_COST;

    if (bank->GetAccountBalance(bankAccountId) < required) {
        Money diff = required - bank->GetAccountBalance(bankAccountId);
        if (cash >= diff) 
        {
            try 
            {
                bank->DepositMoney(bankAccountId, diff);
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
        bank->SendMoney(bankAccountId, marge.bankAccountId, HUSBAND_TO_WIFE_TRANSFER);
        std::cout << "�����: ������� " << HUSBAND_TO_WIFE_TRANSFER << " ���� (�����).\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "�����: ������ �������� ���� -> " << e.what() << "\n";
    }

    try 
    {
        bank->WithdrawMoney(bankAccountId, CHILDREN_ALLOWANCE);
        bart.cash += CHILDREN_ALLOWANCE / 2;
        lisa.cash += CHILDREN_ALLOWANCE / 2;
        std::cout << "�����: ���� " << CHILDREN_ALLOWANCE << " ��� ����� (�� 10 �������).\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "�����: ������ ������ �������� -> " << e.what() << "\n";
    }

    try 
    {
        bank->SendMoney(bankAccountId, burns.bankAccountId, ELECTRICITY_COST);
        std::cout << "�����: ������� ������������� " << ELECTRICITY_COST << ", �������� �� ������.\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "�����: ������ ������ ������������� -> " << e.what() << "\n";
    }
}