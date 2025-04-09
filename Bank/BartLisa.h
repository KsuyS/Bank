#pragma once

#include "Person.h"

class BartLisa : public Person {
private:
    AccountId apuAccount;

public:
    BartLisa(std::string name, Bank& bank, AccountId apuAcc);
    void Act() override;
};