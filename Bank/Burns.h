// �������� �������� - ��� ������� �����, �� ���� ����� ����� ����� ��� �����

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