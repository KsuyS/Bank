#include "PrintHelpers.h"
#include <iostream>

void PrintState(const std::string& message, const Bank& bank, const Homer& homer, const Marge& marge,
    const Bart& bart, const Lisa& lisa, const Apu& apu, const Burns& burns)
{
    std::cout << message << "\n";
    homer.PrintStatus();
    marge.PrintStatus();
    bart.PrintStatus();
    lisa.PrintStatus();
    apu.PrintStatus();
    burns.PrintStatus();
}