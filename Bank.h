#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#include "BankAccount.h"

class Bank {
private:
  string name;
  string address;
  string wh;
  vector<BankAccount *> accounts; // vector of all BankAccounts

public:
  // constructor of Bank
  Bank(string name, string address, string wh) {
    this->name = name;
    this->address = address;
    this->wh = wh;
  }

  // menu
  void menu() {
    char init_choice[100];
    int choice;
    do {
      cout << endl;
      cout << "Eligble servises for Bank: \"" << name << "\"" << endl;
      cout << "  1. Number of bank accounts" << endl;          //+
      cout << "  2. Number of saving bank accounts" << endl;   //+
      cout << "  3. Number of checking bank accounts" << endl; //+
      cout << "  4. Open bank account" << endl;                //+
      cout << "  5. Close bank account" << endl;               //+
      cout << "  6. Modify bank account" << endl;              //+
      cout << "  7. Detailed bank accounts" << endl;           //+
      cout << "  8. Brief bank accounts" << endl;              //+
      cout << "  9. Exit" << endl;                             //+

      cout << "Enter your choice: ";
      cin >> init_choice;
      choice = atoi(init_choice);

      switch (choice) {
      case 1:
        this->showNumberOfBankAccounts();
        break;
      case 2:
        this->showNumberOfSavingAccounts();
        break;
      case 3:
        this->showNumberOfCheckingAccounts();
        break;
      case 4:
        this->openBankAccount();
        break;
      case 5:
        this->closeBankAccount();
        break;
      case 6:
        this->modifyBankAccount();
        break;
      case 7:
        this->printDetailed();
        break;
      case 8:
        this->printBrief();
        break;
      case 9:
        this->exit();
        break;
      default:
        cout << "### Invalid choice. Please try again." << endl;
        break;
      }
      cout << endl;
    } while (choice != 9);
  }

  // get number of Bank Accounts
  void showNumberOfBankAccounts() {
    cout << "| Number of all bank accounts: " << accounts.size() << "\n";
  }

  // get number of Saving Accounts
  void showNumberOfSavingAccounts() {
    int count = 0;
    for (auto acc : accounts) {
      count += acc->getNumberOfSavingAccounts();
    }
    cout << "| Number of all saving accounts: " << count << "\n";
  }

  // get number of Checking Accounts
  void showNumberOfCheckingAccounts() {
    int count = 0;
    for (auto acc : accounts) {
      count += acc->getNumberOfCheckingAccounts();
    }
    cout << "| Number of all checking accounts: " << count << "\n";
  }

  // open Bank-Account
  void openBankAccount() {
    cout << endl;
    cout << "> Enter first name of the account holder: ";
    string firstName;
    cin >> firstName;
    cout << "> Enter the last name of account holder: ";
    string lastName;
    cin >> lastName;
    cout << "> Enter the ssn of account holder: ";
    string ssn;
    cin >> ssn;
    BankAccount *acc = new BankAccount(firstName, lastName, ssn);
    accounts.push_back(acc);
    cout << "| A new Bank Account " << acc->getAccountNumber()
         << " was successfully created" << endl;
    acc->menu();
  }

  // close Bank-Account - in process
  void closeBankAccount() {
    cout << endl;
    cout << "> Enter bank account number to close: ";
    string account_number;
    cin >> account_number;
    auto it = find_if(accounts.begin(), accounts.end(), [&](BankAccount *acc) {
      return acc->getAccountNumber() == account_number;
    });
    if (it == accounts.end()) {
      cout << "### Account not found" << endl;
      return;
    }
    delete *it; // calls bank account's destructor and releases the memory allocated for the object
    accounts.erase(it); // removes the pointer to bank account object from 'accounts' collection
    cout << "| Account closed successfully." << endl;
  }

  // modify Bank Account
  void modifyBankAccount() {
    cout << endl;
    cout << "> Enter bank account number to modify: ";
    string account_number;
    cin >> account_number;
    auto it = find_if(accounts.begin(), accounts.end(), [&](BankAccount *acc) {
      return acc->getAccountNumber() == account_number;
    });
    if (it == accounts.end()) {
      cout << "### Account not found." << endl;
      return;
    }
    (*it)->menu();
  }

  // print Detailed
  void printDetailed() {
    printBrief();
    cout << endl;
    for (auto *acc : accounts) {
      cout << "| Bank Account Number: " << acc->getAccountNumber() << endl;
      cout << "| Account Holder Full Name: " << acc->getFirstName() << " "
           << acc->getLastName() << endl;
      cout << "| Account Holder SSN: " << acc->getSSN() << endl;
      cout << "| Aggregated Balance: " << acc->getBalance() << endl;
      cout << "| Consists of " << (acc->getSubAccounts()).size()
           << " Sub-Accounts" << endl;
      acc->printDetailed();
      cout << endl;
    }
  }

  // print Brief
  void printBrief() {
    cout << endl;
    cout << "| Bank Name: " << name << endl;
    cout << "| Bank Address: " << address << endl;
    cout << "| Bank Working Hours: " << wh << endl;
    double sum = 0;
    for (auto acc : accounts) {
      sum += acc->getBalance();
    }
    cout << "| Aggregated Balance: " << sum << endl;
    cout << "| Consists of " << accounts.size() << " Bank-Accounts" << endl;

    sort(accounts.begin(), accounts.end(),
     [&](BankAccount *bankAcc1, BankAccount *bankAcc2) {
       return bankAcc1->getBalance() > bankAcc2->getBalance();
     });
    for (auto acc : accounts) {
      cout << "| Aggregated balance of the bank account: "
           << acc->getAccountNumber() << " with "
           << (acc->getSubAccounts()).size() << " Sub-Accounts is "
           << acc->getBalance() << endl;
    }
    cout << endl;
  }

  // exit
  void exit() {
    cout << endl;
    cout << "| End of servise for bank \"" << name << "\"" << endl;
  }
};
