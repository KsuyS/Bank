#include "Homer.h"
#include "Constants.h"
#include <iostream>

Homer::Homer(Money initialCash, Bank* bank, Person& marge, Person& bart, Person& lisa, Burns& burns)
    : Person("Homer", initialCash, bank), marge(marge), bart(bart), lisa(lisa), burns(burns) {}

void Homer::Act() 
{
    Money required = HUSBAND_TO_WIFE_TRANSFER + CHILDREN_ALLOWANCE + ELECTRICITY_COST;

    if (bank->GetAccountBalance(bankAccountId) < required) {
        Money diff = required - bank->GetAccountBalance(bankAccountId);
        if (cash >= diff) 
        {
            try 
            {
                bank->DepositMoney(bankAccountId, diff);
                cash -= diff;
                std::cout << "Homer: положил " << diff << " на счёт.\n";
            }
            catch (const BankOperationError& e) 
            {
                std::cout << "Homer: ошибка депозита -> " << e.what() << "\n";
            }
        }
        else 
        {
            std::cout << "Homer: недостаточно личных наличных для депозита (требуется " << diff << ", имеется " << cash << ").\n";
        }
    }

    try 
    {
        bank->SendMoney(bankAccountId, marge.bankAccountId, HUSBAND_TO_WIFE_TRANSFER);
        std::cout << "Homer: перевел " << HUSBAND_TO_WIFE_TRANSFER << " жене (Мардж).\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "Homer: ошибка перевода жене -> " << e.what() << "\n";
    }

    try 
    {
        bank->WithdrawMoney(bankAccountId, CHILDREN_ALLOWANCE);
        bart.cash += CHILDREN_ALLOWANCE / 2;
        lisa.cash += CHILDREN_ALLOWANCE / 2;
        std::cout << "Homer: снял " << CHILDREN_ALLOWANCE << " для детей (по 10 каждому).\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "Homer: ошибка снятия наличных -> " << e.what() << "\n";
    }

    try 
    {
        bank->SendMoney(bankAccountId, burns.bankAccountId, ELECTRICITY_COST);
        std::cout << "Homer: оплатил электричество " << ELECTRICITY_COST << ", переведя их Burns.\n";
    }
    catch (const BankOperationError& e) 
    {
        std::cout << "Homer: ошибка оплаты электричества -> " << e.what() << "\n";
    }
}