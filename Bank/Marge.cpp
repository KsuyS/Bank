#include "Marge.h"
#include "Constants.h"
#include <iostream>

Marge::Marge(Money initialCash, Bank* bank, Person& apu)
    : Person("Marge", initialCash, bank), apu(apu) {}

void Marge::Act() 
{
    try 
    {
        bank->SendMoney(bankAccountId, apu.bankAccountId, FOOD_PAYMENT);
        std::cout << "Marge: перевела " << FOOD_PAYMENT << " Apu за продукты.\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "Marge: ошибка перевода за продукты -> " << e.what() << "\n";
    }
}