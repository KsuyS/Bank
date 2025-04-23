#pragma once
#include <unordered_map>
#include <stdexcept>
#include <atomic>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : public std::runtime_error 
{
public:
    BankOperationError(const std::string& message)
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
    AccountId m_nextAccountId = 1;
    void AssertAccountIsCreated(AccountId accountId) const;
    void AssertIsNegativeSumm(Money amount, const std::string& errorMessage) const;
};