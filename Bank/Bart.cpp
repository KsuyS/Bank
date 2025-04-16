#include "Bart.h"
#include "Constants.h"
#include <iostream>

Bart::Bart(Money initialCash, Bank& bank, Person& apu): Person("Bart", initialCash, bank), m_apu(apu) {}

void Bart::Act() 
{
    if (GetCash() >= ITEM_COST)
    {
        SetCash(GetCash() - ITEM_COST);
        m_apu.SetCash(m_apu.GetCash() + ITEM_COST);
        std::cout << "Барт: купил товар за " << ITEM_COST << " наличными у Апу.\n";
    }
    else 
    {
        std::cout << "Барт: недостаточно наличных для покупки.\n";
    }
}