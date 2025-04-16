// �� ���� ������� ����������
// ���������� ��: Person& marge; Person& bart; Person& lisa; Burns& burns; ��� ����� �� ������ ���� public
// bank ���������� �� ������, �� �� ���������

#pragma once
#include "Person.h"
#include "Burns.h"

class Homer : public Person
{
public:
    Homer(Money initialCash, Bank& bank, Person& m_marge, Person& m_bart, Person& m_lisa, Burns& m_burns);
    void Act() override;
private:
    Person& m_marge;
    Person& m_bart;
    Person& m_lisa;
    Burns& m_burns;
};
