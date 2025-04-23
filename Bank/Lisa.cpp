#include "Lisa.h"
#include <iostream>

Lisa::Lisa(Money initialCash, Bank& bank, Person& apu): Person("Lisa", initialCash, bank), m_apu(apu) {}

void Lisa::Act() 
{
    if (GetCash() >= ITEM_COST)
    {
        AddCash(-ITEM_COST);
        m_apu.AddCash(ITEM_COST);
        std::cout << "����: ������ ����� �� " << ITEM_COST << " ��������� � ���.\n";
    }
    else 
    {
        std::cout << "����: ������������ �������� ��� �������.\n";
    }
}