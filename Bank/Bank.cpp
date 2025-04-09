#include "Bank.h"
#include <iostream>

Bank::Bank(Money initialCash) : cashInCirculation(initialCash), nextAccountId(1) {
    if (initialCash < 0) {
        throw BankOperationError("Initial cash cannot be negative");
    }
}

AccountId Bank::OpenAccount() {
    std::lock_guard<std::mutex> lock(bankMutex);
    AccountId newId = nextAccountId++;
    accounts[newId] = 0;
    return newId;
}

Money Bank::CloseAccount(AccountId accountId) {
    std::lock_guard<std::mutex> lock(bankMutex);
    if (accounts.find(accountId) == accounts.end()) {
        throw BankOperationError("Account does not exist");
    }
    Money balance = accounts[accountId];
    cashInCirculation += balance;
    accounts.erase(accountId);
    return balance;
}

void Bank::SendMoney(AccountId src, AccountId dst, Money amount) {
    if (amount < 0) throw std::out_of_range("Cannot send negative amount");

    std::lock_guard<std::mutex> lock(bankMutex);
    if (accounts.find(src) == accounts.end() || accounts.find(dst) == accounts.end()) {
        throw BankOperationError("Invalid account ID");
    }
    if (accounts[src] < amount) {
        throw BankOperationError("Insufficient funds");
    }

    accounts[src] -= amount;
    accounts[dst] += amount;
}

bool Bank::TrySendMoney(AccountId src, AccountId dst, Money amount) {
    try {
        SendMoney(src, dst, amount);
        return true;
    }
    catch (const BankOperationError&) {
        return false;
    }
}

Money Bank::GetCash() const {
    return cashInCirculation;
}

Money Bank::GetAccountBalance(AccountId accountId) const {
    std::lock_guard<std::mutex> lock(bankMutex);
    auto it = accounts.find(accountId);
    if (it == accounts.end()) {
        throw BankOperationError("Account not found");
    }
    return it->second;
}

void Bank::WithdrawMoney(AccountId account, Money amount) {
    if (amount < 0) throw std::out_of_range("Cannot withdraw negative amount");

    std::lock_guard<std::mutex> lock(bankMutex);
    if (accounts.find(account) == accounts.end() || accounts[account] < amount) {
        throw BankOperationError("Invalid withdrawal");
    }

    accounts[account] -= amount;
    cashInCirculation += amount;
}

bool Bank::TryWithdrawMoney(AccountId account, Money amount) {
    try {
        WithdrawMoney(account, amount);
        return true;
    }
    catch (const BankOperationError&) {
        return false;
    }
}

void Bank::DepositMoney(AccountId account, Money amount) {
    if (amount < 0) throw std::out_of_range("Cannot deposit negative amount");

    std::lock_guard<std::mutex> lock(bankMutex);
    if (accounts.find(account) == accounts.end() || cashInCirculation < amount) {
        throw BankOperationError("Invalid deposit");
    }

    cashInCirculation -= amount;
    accounts[account] += amount;
}