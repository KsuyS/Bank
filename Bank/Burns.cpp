// избавиться от лишнего метода, выплата зарплаты - это тот же самый перевод

#include "Burns.h"
#include "Constants.h"
#include <iostream>

Burns::Burns(Money initialCash, Bank& bank): Person("Burns", initialCash, bank) {}

void Burns::SetHomer(Person& homer) 
{
    m_homer = &homer;
}

void Burns::Act()
{
    std::cout << "Бернс: владеет электростанцией и принимает средства.\n";
    if (m_homer != nullptr) {
        if (GetBank().TrySendMoney(GetBankAccountId(), m_homer->GetBankAccountId(), HOMER_SALARY))
        {
            std::cout << "Бернс: выплатил зарплату " << HOMER_SALARY << " Гомеру.\n";
        }
        else 
        {
            std::cout << "Бернс: не удалось выплатить зарплату Гомеру.\n";
        }
    }
}