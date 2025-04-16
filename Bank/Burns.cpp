#include "Burns.h"
#include "Constants.h"
#include <iostream>

Burns::Burns(Money initialCash, Bank* bank, Person& homer): Person("Burns", initialCash, bank), homer(homer) {}

void Burns::Act() 
{
    std::cout << "�����: ������� ��������������� � ��������� ��������.\n";
    try
    {
        bank.SendMoney(bankAccountId, homer.bankAccountId, HOMER_SALARY);
        std::cout << "�����: �������� �������� " << HUSBAND_TO_WIFE_TRANSFER << " ������.\n";
    }
    catch (const BankOperationError& e)
    {
        std::cout << "�����: ������ ������� �������� -> " << e.what() << "\n";
    }
}