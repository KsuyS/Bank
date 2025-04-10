#include "Burns.h"
#include "Constants.h"
#include <iostream>

Burns::Burns(Money initialCash, Bank* bank): Person("Burns", initialCash, bank) {}

void Burns::Act() 
{
    std::cout << "�����: ������� ��������������� � ��������� ��������.\n";
}

void Burns::PaySalaryToHomer(Person& homer, Money salary) 
{
    if (bank->GetAccountBalance(bankAccountId) >= salary) 
    {
        try 
        {
            bank->SendMoney(bankAccountId, homer.bankAccountId, salary);
            std::cout << "�����: �������� �������� ������: " << salary << "\n";
        }
        catch (const BankOperationError& e) 
        {
            std::cout << "�����: ������ ������� �������� -> " << e.what() << "\n";
        }
    }
    else 
    {
        std::cout << "�����: ������������ ������� ��� ������� �������� ������.\n";
    }
}