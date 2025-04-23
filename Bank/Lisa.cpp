#include "Lisa.h"
#include <iostream>

Lisa::Lisa(Money initialCash, Bank& bank, Person& apu): Person("Lisa", initialCash, bank), m_apu(apu) {}

void Lisa::Act() 
{
    if (GetCash() >= ITEM_COST)
    {
        AddCash(-ITEM_COST);
        m_apu.AddCash(ITEM_COST);
        std::cout << "Лиза: купила товар за " << ITEM_COST << " наличными у Апу.\n";
    }
    else 
    {
        std::cout << "Лиза: недостаточно наличных для покупки.\n";
    }
}