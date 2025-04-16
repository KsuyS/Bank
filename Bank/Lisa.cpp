#include "Lisa.h"
#include "Constants.h"
#include <iostream>

Lisa::Lisa(Money initialCash, Bank& bank, Person& apu): Person("Lisa", initialCash, bank), m_apu(apu) {}

void Lisa::Act() 
{
    if (cash >= ITEM_COST) 
    {
        cash -= ITEM_COST;
        m_apu.cash += ITEM_COST;
        std::cout << "����: ������ ����� �� " << ITEM_COST << " ��������� � ���.\n";
    }
    else 
    {
        std::cout << "����: ������������ �������� ��� �������.\n";
    }
}