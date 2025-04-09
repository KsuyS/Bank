#pragma once

#include "Person.h"

class Marge : public Person {
private:
    AccountId apuAccount;

public:
    Marge(Bank& bank, AccountId apuAcc);
    void Act() override;
};