#include "Bart.h"
#include "Constants.h"
#include <iostream>

Bart::Bart(Money initialCash, Bank* bank, Person& apu): Person("Bart", initialCash, bank), apu(apu) {}

void Bart::Act() 
{
    if (cash >= ITEM_COST) 
    {
        cash -= ITEM_COST;
        apu.cash += ITEM_COST;
        std::cout << "Bart: купил товар за " << ITEM_COST << " наличными у Апу.\n";
    }
    else 
    {
        std::cout << "Bart: недостаточно наличных для покупки.\n";
    }
}