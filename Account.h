#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Account {
    string lastName;
    int accountNumber;
    double balance;
};

vector<Account> accounts;

void loadAccountsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Account account;
        ss >> account.lastName >> account.accountNumber >> account.balance;
        accounts.push_back(account);
    }

    file.close();
}

void saveAccountsToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла." << endl;
        return;
    }

    for (const auto& account : accounts) {
        file << account.lastName << " " << account.accountNumber << " " << account.balance << endl;
    }

    file.close();
}

void addNewAccount(const string& lastName, int accountNumber, double initialBalance, const string& filename) {
    Account account = { lastName, accountNumber, initialBalance };
    accounts.push_back(account);
    saveAccountsToFile(filename);
}

void depositToAccount(const string& lastName, double amount, int accountNumber, const string& filename) {
    for (auto& account : accounts) {
        if (account.lastName == lastName && account.accountNumber == accountNumber) {
            account.balance += amount;
            saveAccountsToFile(filename);
            return;
        }
    }
    cout << "Счет не найден." << endl;
}

void withdrawFromAccount(const string& lastName, double amount, const string& filename) {
    double remainingAmount = amount;
    for (auto& account : accounts) {
        if (account.lastName == lastName) {
            if (account.balance >= remainingAmount) {
                account.balance -= remainingAmount;
                remainingAmount = 0;
                break;
            }
            else {
                remainingAmount -= account.balance;
                account.balance = 0;
            }
        }
    }

    if (remainingAmount > 0) {
        cout << "Недостаточно средств для снятия указанной суммы." << endl;
    }
    else {
        saveAccountsToFile(filename);
    }
}

void displayClientAccounts(const string& lastName) {
    double totalBalance = 0;
    cout << "Счета для клиента " << lastName << ":" << endl;
    for (const auto& account : accounts) {
        if (account.lastName == lastName) {
            totalBalance += account.balance;
            cout << "Счет №" << account.accountNumber << " | Баланс: " << account.balance << endl;
        }
    }
    cout << "Общий баланс: " << totalBalance << endl;
}

void closeAccount(const string& lastName, int accountNumber, const string& filename) {
    auto it = accounts.begin();
    while (it != accounts.end()) {
        if (it->lastName == lastName && it->accountNumber == accountNumber) {
            it = accounts.erase(it);
        }
        else {
            ++it;
        }
    }
    saveAccountsToFile(filename);
}