#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// ------------------ Base Class ------------------
class BankAccount {
protected:
    string owner;
    string password;
    double balance;
    vector<string> transactions; // store transaction history

public:
    BankAccount(string n, string pw, double b) : owner(n), password(pw), balance(b) {}

    virtual void deposit(double amount) {
        if (amount <= 0) throw runtime_error("Deposit must be greater than 0!");
        balance += amount;
        transactions.push_back("Deposited: " + to_string(amount));
        cout << "Deposited: " << amount << ". New balance: " << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) throw runtime_error("Withdraw must be greater than 0!");
        if (amount > balance) throw runtime_error("Insufficient funds!");
        balance -= amount;
        transactions.push_back("Withdrawn: " + to_string(amount));
        cout << "Withdrawn: " << amount << ". New balance: " << balance << endl;
    }

    virtual void printInfo() {
        cout << "Owner: " << owner << ", Balance: " << balance << endl;
    }

    virtual void showTransactions() {
        cout << "--- Transaction History for " << owner << " ---\n";
        if (transactions.empty()) cout << "No transactions yet.\n";
        for (auto& t : transactions) cout << t << endl;
    }

    virtual bool authenticate(string pw) {
        return password == pw;
    }

    virtual ~BankAccount() {}
};

// ------------------ Derived Class: SavingsAccount ------------------
class SavingsAccount : public BankAccount {
    double interestRate; // e.g., 5% interest

public:
    SavingsAccount(string n, string pw, double b, double rate) : BankAccount(n, pw, b), interestRate(rate) {}

    void applyInterest() {
        double interest = balance * interestRate / 100;
        balance += interest;
        transactions.push_back("Interest applied: " + to_string(interest));
        cout << "Interest applied: " << interest << ". New balance: " << balance << endl;
    }

    void printInfo() override {
        cout << "[Savings] Owner: " << owner << ", Balance: " << balance
            << ", Interest Rate: " << interestRate << "%" << endl;
    }
};

// ------------------ Derived Class: CheckingAccount ------------------
class CheckingAccount : public BankAccount {
    double overdraftLimit;

public:
    CheckingAccount(string n, string pw, double b, double overdraft) : BankAccount(n, pw, b), overdraftLimit(overdraft) {}

    void withdraw(double amount) override {
        if (amount <= 0) throw runtime_error("Withdraw must be greater than 0!");
        if (amount > balance + overdraftLimit)
            throw runtime_error("Exceeds overdraft limit!");
        balance -= amount;
        transactions.push_back("Withdrawn: " + to_string(amount));
        cout << "Withdrawn: " << amount << ". New balance: " << balance << endl;
    }

    void printInfo() override {
        cout << "[Checking] Owner: " << owner << ", Balance: " << balance
            << ", Overdraft Limit: " << overdraftLimit << endl;
    }
};

// ------------------ Main Program ------------------
int main() {
    vector<BankAccount*> accounts;
    int choice;

    do {
        cout << "\n--- BANK MENU ---\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Apply Interest (Savings only)\n5. Show All Accounts\n6. Show Transaction History\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // clear newline

        if (choice == 1) {
            int type;
            string name, pw;
            double balance, rateOrOverdraft;

            cout << "Enter account type (1: Savings, 2: Checking): ";
            cin >> type;
            cin.ignore();

            cout << "Enter owner name: ";
            getline(cin, name);
            cout << "Set a password: ";
            getline(cin, pw);
            cout << "Enter initial balance: ";
            cin >> balance;
            cin.ignore();

            if (type == 1) {
                cout << "Enter interest rate (%): ";
                cin >> rateOrOverdraft;
                cin.ignore();
                accounts.push_back(new SavingsAccount(name, pw, balance, rateOrOverdraft));
            }
            else if (type == 2) {
                cout << "Enter overdraft limit: ";
                cin >> rateOrOverdraft;
                cin.ignore();
                accounts.push_back(new CheckingAccount(name, pw, balance, rateOrOverdraft));
            }
            else {
                cout << "Invalid account type!" << endl;
            }
        }
        else if (choice == 2 || choice == 3 || choice == 6) {
            int idx;
            string pw;
            cout << "Enter account number (0-" << accounts.size() - 1 << "): ";
            cin >> idx;
            cin.ignore();

            cout << "Enter password: ";
            getline(cin, pw);

            if (!accounts[idx]->authenticate(pw)) {
                cout << "Incorrect password!" << endl;
                continue;
            }

            if (choice == 2) {
                double amt;
                cout << "Enter amount to deposit: ";
                cin >> amt;
                cin.ignore();
                try { accounts[idx]->deposit(amt); }
                catch (runtime_error& e) { cout << "Error: " << e.what() << endl; }
            }
            else if (choice == 3) {
                double amt;
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                cin.ignore();
                try { accounts[idx]->withdraw(amt); }
                catch (runtime_error& e) { cout << "Error: " << e.what() << endl; }
            }
            else if (choice == 6) {
                accounts[idx]->showTransactions();
            }
        }
        else if (choice == 4) {
            for (auto acc : accounts) {
                SavingsAccount* s = dynamic_cast<SavingsAccount*>(acc);
                if (s) s->applyInterest();
            }
        }
        else if (choice == 5) {
            for (int i = 0; i < accounts.size(); i++) {
                cout << i << ". ";
                accounts[i]->printInfo();
            }
        }

    } while (choice != 7);

    // Free dynamic memory
    for (auto acc : accounts) delete acc;

    return 0;
}
