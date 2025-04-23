#pragma once
#include <string>
#include "Bank.h"
#include "Homer.h"
#include "Marge.h"
#include "Bart.h"
#include "Lisa.h"
#include "Apu.h"
#include "Burns.h"

void PrintState(const std::string& message, const Bank& bank, const Homer& homer, const Marge& marge,
    const Bart& bart, const Lisa& lisa, const Apu& apu, const Burns& burns);