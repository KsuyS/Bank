#pragma once
#include "Bank.h"
#include "Homer.h"
#include "Marge.h"
#include "Bart.h"
#include "Lisa.h"
#include "Apu.h"
#include "Burns.h"

using Money = long long;

Money GetOverallInitialTotal();

void CheckBankSystemConsistency(Bank& bank, const Homer& homer, const Marge& marge,
    const Bart& bart, const Lisa& lisa, const Apu& apu, const Burns& burns);