// main.cpp
#include <iostream>
#include <stdexcept>
#include "Bank.h"  // Класс Bank и BankOperationError объявлены в Bank.h
#include <string>
#include <windows.h>

using namespace std;

// Базовый класс для персонажей
class Person {
public:
    string name;
    Money cash;              // личные наличные средства
    AccountId bankAccountId; // идентификатор банковского счета
    Bank* bank;

    Person(const string& n, Money initialCash, Bank* b)
        : name(n), cash(initialCash), bank(b)
    {
        bankAccountId = bank->OpenAccount();
    }

    Money getBankBalance() const {
        return bank->GetAccountBalance(bankAccountId);
    }

    virtual void act() = 0;

    virtual void printStatus() const {
        cout << name << " - Личные наличные: " << cash 
             << ", Счет: " << getBankBalance() << "\n";
    }
    
    virtual ~Person() = default;
};

// Класс Burns – владелец электростанции
class Burns : public Person {
public:
    Burns(Money initialCash, Bank* bank)
        : Person("Burns", initialCash, bank) {}

    void act() override {
        cout << "Burns: владеет электростанцией и принимает средства.\n";
    }
};

// Гомер – переводит деньги жене, снимает деньги для детей и оплачивает электричество.
// Теперь у него имеется прямая ссылка на объект Burns для перевода оплаты электричества.
class Homer : public Person {
public:
    Person& marge;
    Person& bart;
    Person& lisa;
    Burns& burns;  // для оплаты электричества

    Homer(Money initialCash, Bank* bank, Person& m, Person& b, Person& l, Burns& br)
        : Person("Homer", initialCash, bank), marge(m), bart(b), lisa(l), burns(br) {}

    void act() override {
        // Необходимые средства: перевод жене (100) + снятие для детей (20) + оплата электричества (100) = 220.
        Money required = 220;
        if (bank->GetAccountBalance(bankAccountId) < required) {
            Money diff = required - bank->GetAccountBalance(bankAccountId);
            if (cash >= diff) {
                try {
                    bank->DepositMoney(bankAccountId, diff);
                    cash -= diff;
                    cout << "Homer: депонировал " << diff << " для пополнения счета.\n";
                } catch (const BankOperationError& e) {
                    cout << "Homer: ошибка депозита -> " << e.what() << "\n";
                }
            } else {
                cout << "Homer: недостаточно личных наличных для депозита (требуется " 
                     << diff << ", имеется " << cash << ").\n";
            }
        }
        // Перевод жене – 100.
        try {
            bank->SendMoney(bankAccountId, marge.bankAccountId, 100);
            cout << "Homer: перевел 100 Мардж.\n";
        } catch (const BankOperationError& e) {
            cout << "Homer: ошибка перевода жене -> " << e.what() << "\n";
        }
        // Снятие для детей – 20 (по 10 каждому).
        try {
            bank->WithdrawMoney(bankAccountId, 20);
            bart.cash += 10;
            lisa.cash += 10;
            cout << "Homer: снял 20 для детей (по 10 каждому).\n";
        } catch (const BankOperationError& e) {
            cout << "Homer: ошибка снятия наличных -> " << e.what() << "\n";
        }
        // Оплата электричества – 100 (перевод на счет Burns).
        try {
            bank->SendMoney(bankAccountId, burns.bankAccountId, 100);
            cout << "Homer: оплатил электричество 100, переведя их Burns.\n";
        } catch (const BankOperationError& e) {
            cout << "Homer: ошибка оплаты электричества -> " << e.what() << "\n";
        }
    }
};

// Marge – переводит 60 за продукты на счет Apu.
class Marge : public Person {
public:
    Person& apu;
    Marge(Money initialCash, Bank* bank, Person& a)
        : Person("Marge", initialCash, bank), apu(a) {}
    
    void act() override {
        try {
            bank->SendMoney(bankAccountId, apu.bankAccountId, 60);
            cout << "Marge: перевела 60 Апу за продукты.\n";
        } catch (const BankOperationError& e) {
            cout << "Marge: ошибка перевода за продукты -> " << e.what() << "\n";
        }
    }
};

// Bart – покупает товар за 2 наличными у Apu.
class Bart : public Person {
public:
    Person& apu;
    Bart(Money initialCash, Bank* bank, Person& a)
        : Person("Bart", initialCash, bank), apu(a) {}
    
    void act() override {
        Money cost = 2;
        if (cash >= cost) {
            cash -= cost;
            apu.cash += cost;
            cout << "Bart: купил товар за 2 наличными.\n";
        } else {
            cout << "Bart: недостаточно наличных для покупки.\n";
        }
    }
};

// Lisa – покупает товар за 2 наличными у Apu.
class Lisa : public Person {
public:
    Person& apu;
    Lisa(Money initialCash, Bank* bank, Person& a)
        : Person("Lisa", initialCash, bank), apu(a) {}
    
    void act() override {
        Money cost = 2;
        if (cash >= cost) {
            cash -= cost;
            apu.cash += cost;
            cout << "Lisa: купила товар за 2 наличными.\n";
        } else {
            cout << "Lisa: недостаточно наличных для покупки.\n";
        }
    }
};

// Apu – депонирует поступившие наличные на счет и оплачивает электричество 100,
// переводя их на счет Burns.
class Apu : public Person {
public:
    Burns& burns;
    Apu(Money initialCash, Bank* bank, Burns& b)
        : Person("Apu", initialCash, bank), burns(b) {}

    void act() override {
        if (cash > 0) {
            try {
                bank->DepositMoney(bankAccountId, cash);
                cout << "Apu: депонировал " << cash << " наличных на счет.\n";
                cash = 0;
            } catch (const BankOperationError& e) {
                cout << "Apu: ошибка депозита -> " << e.what() << "\n";
            }
        }
        try {
            bank->SendMoney(bankAccountId, burns.bankAccountId, 100);
            cout << "Apu: заплатил за электричество 100, переведя их Burns.\n";
        } catch (const BankOperationError& e) {
            cout << "Apu: ошибка оплаты электричества -> " << e.what() << "\n";
        }
    }
};

//
// Функция main: выводим итоговые состояния участников и банка без проверки инвариантов.
//
int main(int argc, char* argv[]) {
    // Настройка кодировки для Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int iterations = 0;
    if (argc >= 2)
        iterations = std::stoi(argv[1]);
    else {
        cout << "Введите количество итераций: ";
        cin >> iterations;
    }

    // Инициализируем банковскую систему:
    Money initialBankCash = 5000;  // изначальные наличные банка
    Bank bank(initialBankCash);

    // Задаём начальные личные средства персонажей (до депозита):
    // Homer – 1900, Marge – 900, Bart – 500, Lisa – 500, Apu – 800, Burns – 400. Всего 5000.
    Burns burns(400, &bank);
    Apu apu(800, &bank, burns);
    Marge marge(900, &bank, apu);
    Bart bart(500, &bank, apu);
    Lisa lisa(500, &bank, apu);
    Homer homer(1900, &bank, marge, bart, lisa, burns);

    // Выполняем депозит исходных безналичных средств:
    // Для Burns депонируем 200: его личные становятся 400-200 = 200, счет – 200.
    try {
        bank.DepositMoney(burns.bankAccountId, 200);
        burns.cash -= 200;
    } catch (const BankOperationError& e) {
        cout << "Ошибка депозита для Burns: " << e.what() << "\n";
    }
    // Для Apu депонируем 250: его личные становятся 800-250 = 550, счет – 250.
    try {
        bank.DepositMoney(apu.bankAccountId, 250);
        apu.cash -= 250;
    } catch (const BankOperationError& e) {
        cout << "Ошибка депозита для Apu: " << e.what() << "\n";
    }
    // Для Homer депонируем 200: его личные становятся 1900-200 = 1700, счет – 200.
    try {
        bank.DepositMoney(homer.bankAccountId, 200);
        homer.cash -= 200;
    } catch (const BankOperationError& e) {
        cout << "Ошибка депозита для Homer: " << e.what() << "\n";
    }
    // После депозитов:
    // Личные: Homer 1700, Marge 900, Bart 500, Lisa 500, Apu 550, Burns 200. Всего 4350.
    // Счета: Homer 200, Marge 0, Bart 0, Lisa 0, Apu 250, Burns 200. Всего 650.
    // Наличные банка: 5000 - (200+250+200) = 4350.
    // Общая сумма системы = 4350 + 4350 + 650 = 9350.

    // Пересчитаем исходную сумму средств:
    Money totalInitial = bank.GetCash() +
                         (homer.cash + marge.cash + bart.cash + lisa.cash + apu.cash + burns.cash) +
                         (homer.getBankBalance() + marge.getBankBalance() + bart.getBankBalance() +
                          lisa.getBankBalance() + apu.getBankBalance() + burns.getBankBalance());
    
    // Вывод начального состояния:
    cout << "\n=== Начальное состояние ===\n";
    homer.printStatus();
    marge.printStatus();
    bart.printStatus();
    lisa.printStatus();
    apu.printStatus();
    burns.printStatus();
    cout << "Наличные банка: " << bank.GetCash() << "\n";
    cout << "Исходная сумма средств: " << totalInitial << "\n";

    cout << "\nНачало симуляции. Итераций: " << iterations << "\n";

    // Основной цикл симуляции.
    for (int i = 1; i <= iterations; i++) {
        cout << "\n=== Итерация " << i << " ===\n";

        homer.act();
        marge.act();
        bart.act();
        lisa.act();
        apu.act();
        // Выплата зарплаты от Burns Гомеру: 50 (если у Burns достаточно средств)
        Money salary = 50;
        if (burns.getBankBalance() >= salary) {
            try {
                bank.SendMoney(burns.bankAccountId, homer.bankAccountId, salary);
                cout << "Burns: выплатил зарплату Гомеру: " << salary << "\n";
            } catch (const BankOperationError& e) {
                cout << "Burns: ошибка выплаты зарплаты -> " << e.what() << "\n";
            }
        }
        burns.act();

        cout << "\nСостояние после итерации " << i << ":\n";
        homer.printStatus();
        marge.printStatus();
        bart.printStatus();
        lisa.printStatus();
        apu.printStatus();
        burns.printStatus();
        cout << "Наличные банка: " << bank.GetCash() << "\n";
    }

    // Итоговый вывод состояний:
    cout << "\n=== Итоги симуляции ===\n";
    homer.printStatus();
    marge.printStatus();
    bart.printStatus();
    lisa.printStatus();
    apu.printStatus();
    burns.printStatus();
    cout << "Наличные банка: " << bank.GetCash() << "\n";

    return 0;
}