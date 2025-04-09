#pragma once

#include "Person.h"

class Apu : public Person {
private:
    AccountId burnsAccount;

public:
    Apu(Bank& bank, AccountId burnsAcc);
    void Act() override;
};