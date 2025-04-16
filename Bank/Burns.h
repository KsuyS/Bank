// выпалата зарплаты - это перевод денег, по сути зачем новый метод для этого

#pragma once
#include "Person.h"
#include "Homer.h"

class Burns : public Person 
{
public:
    Person& homer;
    Burns(Money initialCash, Bank* bank, Person& homer);
    void Act() override;
};