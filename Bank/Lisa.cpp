#include "Lisa.h"
#include "Constants.h"
#include <iostream>

Lisa::Lisa(Money initialCash, Bank* bank, Person& apu)
    : Person("Lisa", initialCash, bank), apu(apu) {}

void Lisa::Act() 
{
    if (cash >= ITEM_COST) 
    {
        cash -= ITEM_COST;
        apu.cash += ITEM_COST;
        std::cout << "Lisa: купила товар за " << ITEM_COST << " наличными у Аpu.\n";
    }
    else 
    {
        std::cout << "Lisa: недостаточно наличных для покупки.\n";
    }
}