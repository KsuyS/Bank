// �� ���� ������� ����������
// Person& marge; Person& bart; Person& lisa; Burns& burns; ��� ����� �� ������ ���� public
// bank ���������� �� ������, �� �� ���������

#pragma once
#include "Person.h"
#include "Burns.h"

class Homer : public Person
{
public:
    Homer(Money initialCash, Bank& bank, Person& m_marge, Person& m_bart, Person& m_lisa, Person& m_burns);
    void Act() override;
    void TransferToWife();
    void WithdrawForChildren();
    void PayElectricity();
    void DepositRemainingCash();
private:
    Person& m_marge;
    Person& m_bart;
    Person& m_lisa;
    Person& m_burns;
};
