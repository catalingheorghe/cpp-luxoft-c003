/* Account class, two derived subclasses */

#include <iostream>

class Account {
protected:
    int accountNumber;
    std::string owner;
    double balance;
public:
    Account (int number, std::string& name) : accountNumber{number}, owner{name}, balance{0} { }

    virtual void deposit(double amount) { balance += amount; }
    virtual void withdraw(double amount) { balance -= amount; }

    void print() const {
        std::cout << "account(" << accountNumber << " " << owner 
            << " : " << balance << ");" << std::endl;
    }
};

class SavingsAccount : public Account {
public:
    using Account::Account;

    void withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;
        } else {
            std::cout << "Balance insufficient" << std::endl;
        }
    }
};

class CheckingAccount : public Account {
public:
    using Account::Account;

    // TODO override, no override, what is the difference?
    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            double fee = amount * 0.01;
            balance -= amount;
            std::cout << "Going below 0 with a " << fee << "$ fee" << std::endl;
            balance -= fee;
        }
    }
};

int main()
{
    std::string name{"JD"};
    Account acc{1, name};

    acc.deposit(3000);
    acc.deposit(2000);
    acc.withdraw(1500);
    acc.print(); // 3500

    name = "Savester";
    SavingsAccount savings{2, name};
    savings.deposit(5000);
    savings.withdraw(4000); // 1000
    savings.withdraw(3000); // still 1000
    savings.print();

    name = "Crediter";
    CheckingAccount credit{3, name};
    credit.deposit(5000);
    credit.withdraw(4000);
    credit.withdraw(3000);
    credit.print();

    std::cout << std::endl;

    acc = savings; // copy into an Account object, no longer savings
    acc.deposit(5000);  // 6000
    acc.withdraw(4000); // 2000
    acc.withdraw(3000); // -1000 (normal account)
    acc.print();

    std::cout << std::endl;

    Account* a = &savings; // this is still a savings account
    a->deposit(5000);  // 6000 (first "savings")
    a->withdraw(4000); // 2000
    a->withdraw(3000); // still 2000
    a->print();

    std::cout << std::endl;

    name = "Another Savester";
    Account *b = new SavingsAccount(100, name);
    b->deposit(1000);
    b->withdraw(2000); // still 1000
    b->print();
}
