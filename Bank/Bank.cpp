// вынести повторяющийся код в AssertAccountIsCreated и AssertIsNegativeSumm

#include "Bank.h"
#include <iostream>

Bank::Bank(Money initialCash) : m_cashInCirculation(initialCash), m_nextAccountId(1)
{
    AssertIsNegativeSumm(initialCash, "Первоначальный размер денежных средств не может быть отрицательным!");
}

AccountId Bank::OpenAccount()
{
    AccountId newId = m_nextAccountId++;
    m_accounts[newId] = 0;
    return newId;
}

Money Bank::CloseAccount(AccountId accountId)
{
    AssertAccountIsCreated(accountId);

    Money balance = m_accounts[accountId];
    m_cashInCirculation += balance;
    m_accounts.erase(accountId);
    return balance;
}

void Bank::SendMoney(AccountId src, AccountId dst, Money amount)
{
    AssertIsNegativeSumm(amount, "Невозможно отправить отрицательную сумму!");
    AssertAccountIsCreated(src);
    AssertAccountIsCreated(dst);

    if (m_accounts[src] < amount)
    {
        throw BankOperationError("Недостаточно средств!");
    }

    m_accounts[src] -= amount;
    m_accounts[dst] += amount;
}

bool Bank::TrySendMoney(AccountId src, AccountId dst, Money amount)
{
    try
    {
        SendMoney(src, dst, amount);
        return true;
    }
    catch (const BankOperationError&)
    {
        return false;
    }
}

Money Bank::GetCash() const
{
    return m_cashInCirculation;
}

Money Bank::GetAccountBalance(AccountId accountId) const
{
    AssertAccountIsCreated(accountId);
    return m_accounts.at(accountId);
}

void Bank::WithdrawMoney(AccountId account, Money amount)
{
    AssertIsNegativeSumm(amount, "Невозможно снять отрицательную сумму!");
    AssertAccountIsCreated(account);

    if (m_accounts[account] < amount)
    {
        throw BankOperationError("Недействительный вывод средств!");
    }

    m_accounts[account] -= amount;
    m_cashInCirculation += amount;
}

bool Bank::TryWithdrawMoney(AccountId account, Money amount)
{
    try
    {
        WithdrawMoney(account, amount);
        return true;
    }
    catch (const BankOperationError&)
    {
        return false;
    }
}

void Bank::DepositMoney(AccountId account, Money amount)
{
    AssertIsNegativeSumm(amount, "Невозможно внести отрицательную сумму!");
    AssertAccountIsCreated(account);

    if (m_cashInCirculation < amount)
    {
        throw BankOperationError("Недействительный депозит!");
    }

    m_cashInCirculation -= amount;
    m_accounts[account] += amount;
}

void Bank::AssertAccountIsCreated(AccountId accountId) const
{
    if (m_accounts.find(accountId) == m_accounts.end())
    {
        throw BankOperationError("Аккаунт не существует!");
    }
}

void Bank::AssertIsNegativeSumm(Money amount, const std::string& errorMessage) const
{
    if (amount < 0)
    {
        throw std::out_of_range(errorMessage);
    }
}