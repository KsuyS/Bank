// ���������� �� ������� ������, ������� �������� - ��� ��� �� ����� �������

#include "Burns.h"
#include "Constants.h"
#include <iostream>

Burns::Burns(Money initialCash, Bank& bank): Person("Burns", initialCash, bank) {}

void Burns::SetHomer(Person& homer) 
{
    m_homer = &homer;
}

void Burns::Act()
{
    std::cout << "�����: ������� ��������������� � ��������� ��������.\n";
    if (m_homer != nullptr) {
        if (bank.TrySendMoney(bankAccountId, m_homer->bankAccountId, HOMER_SALARY)) 
        {
            std::cout << "�����: �������� �������� " << HOMER_SALARY << " ������.\n";
        }
        else 
        {
            std::cout << "�����: �� ������� ��������� �������� ������.\n";
        }
    }
}