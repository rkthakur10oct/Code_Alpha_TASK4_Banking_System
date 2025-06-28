#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string date;
    string toAccount;

    Transaction(string t, double amt, string toAcc = "") {
        type = t;
        amount = amt;
        toAccount = toAcc;
        time_t now = time(0);
        date = ctime(&now);
        date.pop_back(); // Remove newline
    }

    void show() {
        cout << fixed << setprecision(2);
        cout << "[" << date << "] " << type;
        if (!toAccount.empty()) cout << " to " << toAccount;
        cout << ": ₹" << amount << endl;
    }
};

class Account {
public:
    string accountNumber;
    double balance;
    vector<Transaction> history;

    Account(string accNum) {
        accountNumber = accNum;
        balance = 0.0;
    }

    void deposit(double amount) {
        balance += amount;
        history.emplace_back("Deposit", amount);
    }

    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        history.emplace_back("Withdrawal", amount);
        return true;
    }

    bool transfer(Account& toAcc, double amount) {
        if (amount > balance) return false;
        balance -= amount;
        toAcc.balance += amount;
        history.emplace_back("Transfer", amount, toAcc.accountNumber);
        toAcc.history.emplace_back("Received", amount, accountNumber);
        return true;
    }

    void showTransactions() {
        cout << "\nTransaction History for Account: " << accountNumber << endl;
        if (history.empty()) {
            cout << "No transactions yet.\n";
        } else {
            for (auto& t : history) t.show();
        }
    }

    void showInfo() {
        cout << "\nAccount: " << accountNumber << " | Balance: ₹" << fixed << setprecision(2) << balance << endl;
    }
};

class Customer {
public:
    string name;
    string customerID;
    Account account;

    Customer(string n, string id, string accNum) : account(accNum) {
        name = n;
        customerID = id;
    }

    void showProfile() {
        cout << "\nCustomer: " << name << " (ID: " << customerID << ")\n";
        account.showInfo();
    }
};

// ========== Main Program ==========
int main() {
    vector<Customer> customers;

    while (true) {
        cout << "\n==== Banking System Menu ====\n";
        cout << "1. Create Customer\n2. Deposit\n3. Withdraw\n4. Transfer\n5. View Transactions\n6. View Account Info\n0. Exit\nChoose: ";
        int choice;
        cin >> choice;

        if (choice == 0) break;

        string id;
        double amount;
        switch (choice) {
            case 1: {
                string name, id, acc;
                cout << "Enter Name: "; cin >> ws; getline(cin, name);
                cout << "Enter Customer ID: "; cin >> id;
                cout << "Enter Account Number: "; cin >> acc;
                customers.emplace_back(name, id, acc);
                cout << "Customer created.\n";
                break;
            }
            case 2: {
                cout << "Enter Customer ID: "; cin >> id;
                cout << "Amount to deposit: ₹"; cin >> amount;
                for (auto& c : customers) {
                    if (c.customerID == id) {
                        c.account.deposit(amount);
                        cout << "Deposited successfully.\n";
                        break;
                    }
                }
                break;
            }
            case 3: {
                cout << "Enter Customer ID: "; cin >> id;
                cout << "Amount to withdraw: ₹"; cin >> amount;
                for (auto& c : customers) {
                    if (c.customerID == id) {
                        if (c.account.withdraw(amount))
                            cout << "Withdrawn successfully.\n";
                        else
                            cout << "Insufficient balance!\n";
                        break;
                    }
                }
                break;
            }
            case 4: {
                string toID;
                cout << "From Customer ID: "; cin >> id;
                cout << "To Customer ID: "; cin >> toID;
                cout << "Amount to transfer: ₹"; cin >> amount;
                Account *from = nullptr, *to = nullptr;
                for (auto& c : customers) {
                    if (c.customerID == id) from = &c.account;
                    if (c.customerID == toID) to = &c.account;
                }
                if (from && to) {
                    if (from->transfer(*to, amount))
                        cout << "Transfer successful.\n";
                    else
                        cout << "Insufficient balance!\n";
                } else {
                    cout << "Customer ID(s) not found.\n";
                }
                break;
            }
            case 5: {
                cout << "Enter Customer ID: "; cin >> id;
                for (auto& c : customers) {
                    if (c.customerID == id) {
                        c.account.showTransactions();
                        break;
                    }
                }
                break;
            }
            case 6: {
                cout << "Enter Customer ID: "; cin >> id;
                for (auto& c : customers) {
                    if (c.customerID == id) {
                        c.showProfile();
                        break;
                    }
                }
                break;
            }
            default:
                cout << "Invalid option.\n";
        }
    }

    return 0;
}
