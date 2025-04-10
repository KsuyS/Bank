#pragma once

#include <unordered_map>
#include <stdexcept>
#include <mutex>
#include <atomic>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : public std::runtime_error 
{
public:
    explicit BankOperationError(const std::string& message)
        : std::runtime_error(message) {}
};

class Bank 
{
public:
    explicit Bank(Money initialCash);

    AccountId OpenAccount();
    Money CloseAccount(AccountId accountId);

    void SendMoney(AccountId src, AccountId dst, Money amount);
    bool TrySendMoney(AccountId src, AccountId dst, Money amount);

    Money GetCash() const;
    Money GetAccountBalance(AccountId accountId) const;

    void WithdrawMoney(AccountId account, Money amount);
    bool TryWithdrawMoney(AccountId account, Money amount);

    void DepositMoney(AccountId account, Money amount);

private:
    Money m_cashInCirculation;
    std::unordered_map<AccountId, Money> m_accounts;
    mutable std::mutex m_bankMutex;
    std::atomic<AccountId> m_nextAccountId;
};