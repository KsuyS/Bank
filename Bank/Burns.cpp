#include "Burns.h"
#include "Constants.h"
#include <iostream>

Burns::Burns(Money initialCash, Bank* bank, Person& homer): Person("Burns", initialCash, bank), homer(homer) {}

void Burns::Act() 
{
    std::cout << "Бернс: владеет электростанцией и принимает средства.\n";
    try
    {
        bank.SendMoney(bankAccountId, homer.bankAccountId, HOMER_SALARY);
        std::cout << "Бернс: выплатил зарплату " << HUSBAND_TO_WIFE_TRANSFER << " Гомеру.\n";
    }
    catch (const BankOperationError& e)
    {
        std::cout << "Бернс: ошибка выплаты зарплаты -> " << e.what() << "\n";
    }
}