#include "Bart.h"
#include <iostream>

Bart::Bart(Money initialCash, Bank& bank, Person& apu): Person("Bart", initialCash, bank), m_apu(apu) {}

void Bart::Act() 
{
    if (GetCash() >= ITEM_COST)
    {
        AddCash(-ITEM_COST);
        m_apu.AddCash(ITEM_COST);
        std::cout << "����: ����� ����� �� " << ITEM_COST << " ��������� � ���.\n";
    }
    else 
    {
        std::cout << "����: ������������ �������� ��� �������.\n";
    }
}