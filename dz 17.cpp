#include "Account.h"

int main()
{
    const string filename = "bankAccounts.txt";
    loadAccountsFromFile(filename);

    // Пример использования функций
    addNewAccount("Иванов", 1001, 5000, filename);
    addNewAccount("Петров", 1002, 3000, filename);
    depositToAccount("Иванов", 2000, 1001, filename);
    displayClientAccounts("Иванов");
    cout << "------------------\n";
    withdrawFromAccount("Иванов", 7000, filename);
    displayClientAccounts("Иванов");
    cout << "-------------------------\n";
    closeAccount("Петров", 1002, filename);

    return 0;
}
