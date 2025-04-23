#include "Bart.h"
#include <iostream>

Bart::Bart(Money initialCash, Bank& bank, Person& apu): Person("Bart", initialCash, bank), m_apu(apu) {}

void Bart::Act() 
{
    if (GetCash() >= ITEM_COST)
    {
        AddCash(-ITEM_COST);
        m_apu.AddCash(ITEM_COST);
        std::cout << "Барт: купил товар за " << ITEM_COST << " наличными у Апу.\n";
    }
    else 
    {
        std::cout << "Барт: недостаточно наличных для покупки.\n";
    }
}