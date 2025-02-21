/* Account class, two derived subclasses */

#include <iostream>
#include <vector>

class Account {
protected:
    int accountNumber;
    std::string owner;
    double balance;
    std::vector<std::string> transactions;
    enum OperationType { Credit, Debit };

    void logTransaction(OperationType type, double amount, double balance) {
        std::string tran = "";
        if (type == Credit) {
            tran += "> Credit ";
        } else if (type == Debit) {
            tran += "> Debit  ";
        } else {
            return;
        }
        tran += std::to_string(amount);
        tran += " (balance: ";
        tran += std::to_string(balance);
        tran += ")\n";
        transactions.insert(transactions.begin(), tran);
    }

public:
    Account (int number, std::string& name)
        : accountNumber{number}, owner{name}, balance{0}, transactions{}  { }

    virtual void deposit(double amount) {
        balance += amount;
        logTransaction(Credit, amount, balance);
    }
    virtual void withdraw(double amount) {
        balance -= amount;
        logTransaction(Debit, amount, balance);
    }

    void print() const {
        std::cout << "account(" << accountNumber << " " << owner 
            << " : " << balance << ");" << std::endl;
    }

    void listTransactions() const {
        for (std::string t : transactions) {
            std::cout << t;
        }
    }
};

class SavingsAccount : public Account {
public:
    using Account::Account;

    void withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;
            logTransaction(Debit, amount, balance);
        } else {
            std::cout << "Balance insufficient" << std::endl;
        }
    }
};

class CheckingAccount : public Account {
public:
    using Account::Account;

    // override, no override, what is the difference?
    // -> tell the compiler that you want to override a function that must exist
    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            logTransaction(Debit, amount, balance);
        } else {
            double fee = amount * 0.01;
            balance -= amount;
            std::cout << "Going below 0 with a " << fee << "$ fee" << std::endl;
            balance -= fee;
            logTransaction(Debit, amount + fee, balance);
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
    acc.listTransactions();

    name = "Savester";
    SavingsAccount savings{2, name};
    savings.deposit(5000);
    savings.withdraw(4000); // 1000
    savings.withdraw(3000); // still 1000
    savings.print();
    savings.listTransactions();

    name = "Crediter";
    CheckingAccount credit{3, name};
    credit.deposit(5000);
    credit.withdraw(4000);
    credit.withdraw(3000);
    credit.print();
    credit.listTransactions();

    std::cout << std::endl;

    acc = savings; // copy into an Account object, no longer savings
    // (!) this would be OBJECT SLICING, but there are no extra in the subclass
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
