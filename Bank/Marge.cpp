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
        std::cout << "Marge: �������� " << FOOD_PAYMENT << " Apu �� ��������.\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "Marge: ������ �������� �� �������� -> " << e.what() << "\n";
    }
}