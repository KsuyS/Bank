// выпалата зарплаты - это перевод денег, зачем новый метод для этого

#pragma once
#include "Person.h"
#include "Homer.h"

class Burns : public Person
{
public:
    Burns(Money initialCash, Bank& bank);
    void SetHomer(Person& homer);
    void Act() override;
private:
    Person* m_homer = nullptr;
};