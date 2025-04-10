// вынести повторяющийся код в AssertAccountIsCreated и AssertIsNegativeSumm

#include "Bank.h"
#include <iostream>

Bank::Bank(Money initialCash) : m_cashInCirculation(initialCash), m_nextAccountId(1) 
{
    if (initialCash < 0) 
    {
        throw BankOperationError("Первоначальный размер денежных средств не может быть отрицательным!");
    }
}

AccountId Bank::OpenAccount() 
{
    std::lock_guard<std::mutex> lock(m_bankMutex);
    AccountId newId = m_nextAccountId++;
    m_accounts[newId] = 0;
    return newId;
}

Money Bank::CloseAccount(AccountId accountId) 
{
    std::lock_guard<std::mutex> lock(m_bankMutex);
    if (m_accounts.find(accountId) == m_accounts.end()) 
    {
        throw BankOperationError("Аккаунт не существует!");
    }
    Money balance = m_accounts[accountId];
    m_cashInCirculation += balance;
    m_accounts.erase(accountId);
    return balance;
}

void Bank::SendMoney(AccountId src, AccountId dst, Money amount) 
{
    if (amount < 0) throw std::out_of_range("Невозможно отправить отрицательную сумму!");

    std::lock_guard<std::mutex> lock(m_bankMutex);
    if (m_accounts.find(src) == m_accounts.end() || m_accounts.find(dst) == m_accounts.end()) 
    {
        throw BankOperationError("Неверный идентификатор учетной записи!");
    }
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
    std::lock_guard<std::mutex> lock(m_bankMutex);
    auto it = m_accounts.find(accountId);
    if (it == m_accounts.end()) 
    {
        throw BankOperationError("Аккаунт не найден!");
    }
    return it->second;
}

void Bank::WithdrawMoney(AccountId account, Money amount) 
{
    if (amount < 0) throw std::out_of_range("Невозможно снять отрицательную сумму!");

    std::lock_guard<std::mutex> lock(m_bankMutex);
    if (m_accounts.find(account) == m_accounts.end() || m_accounts[account] < amount) 
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
    if (amount < 0) throw std::out_of_range("Невозможно внести отрицательную сумму!");

    std::lock_guard<std::mutex> lock(m_bankMutex);
    if (m_accounts.find(account) == m_accounts.end() || m_cashInCirculation < amount) 
    {
        throw BankOperationError("Недействительный депозит!");
    }

    m_cashInCirculation -= amount;
    m_accounts[account] += amount;
}