#include "Burns.h"
#include "Constants.h"
#include <iostream>

Burns::Burns(Money initialCash, Bank* bank): Person("Burns", initialCash, bank) {}

void Burns::Act() 
{
    std::cout << "Burns: владеет электростанцией и принимает средства.\n";
}

void Burns::PaySalaryToHomer(Person& homer, Money salary) 
{
    if (bank->GetAccountBalance(bankAccountId) >= salary) 
    {
        try 
        {
            bank->SendMoney(bankAccountId, homer.bankAccountId, salary);
            std::cout << "Burns: выплатил зарплату Гомеру: " << salary << "\n";
        }
        catch (const BankOperationError& e) 
        {
            std::cout << "Burns: ошибка выплаты зарплаты -> " << e.what() << "\n";
        }
    }
    else 
    {
        std::cout << "Burns: недостаточно средств для выплаты зарплаты Гомеру.\n";
    }
}