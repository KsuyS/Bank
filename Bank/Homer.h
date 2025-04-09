#pragma once

#include "Person.h"

class Homer : public Person {
private:
    AccountId margeAccount;
    AccountId burnsAccount;

public:
    Homer(Bank& bank, AccountId margeAcc, AccountId burnsAcc);
    void Act() override;
};