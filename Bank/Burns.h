#pragma once

#include "Person.h"

class Burns : public Person {
public:
    Burns(Bank& bank);
    void Act() override;
};