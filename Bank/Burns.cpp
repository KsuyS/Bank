#include "Burns.h"
#include <iostream>

Burns::Burns(Bank& bank) : Person("Burns", 0, bank) {}

void Burns::Act() {
    std::cout << "Burns ������ �� ������, ������ ������� ���������������\n";
}