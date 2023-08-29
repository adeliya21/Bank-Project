#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#include "SubAccount.h"

class BankAccount {

private:
  string firstName;
  string lastName;
  string ssn;
  vector<SubAccount *> subAccounts; // vector of Sub-Accounts
  string accountNumber;             // bank-account number
  static int accountNumberCounter;  // bank-account number counter

public:
  // constructor of Bank Account
  BankAccount(string firstName, string lastName, string ssn) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->ssn = ssn;
    // generate unique account number
    accountNumber = "BNK" + to_string(accountNumberCounter++);
  }

  // destructor of Bank Acccount
  ~BankAccount() {
    cout << "In bank account destructor" << endl;
    while (!subAccounts.empty()) {
      delete subAccounts.front(); // calls sub-account's destructor and releases the memory allocated for the object
      subAccounts.erase(subAccounts.begin()); // removes the pointer to sub-acount object from 'subAccounts' collection
    }
    cout << "Sub accounts are deleted." << endl;
  }

  // methods used in Bank menu

  // get first name
  string getFirstName() { return firstName; }

  // get last name
  string getLastName() { return lastName; }

  // get SSN
  string getSSN() { return ssn; }

  // get account Number
  string getAccountNumber() { return accountNumber; }

  // get Sub Accounts
  vector<SubAccount *> getSubAccounts() { return subAccounts; }

  // get balance
  double getBalance() {
    double sum = 0;
    for (auto subAcc : subAccounts) {
      sum += subAcc->getBalance();
    }
    return sum;
  }

  // get number of Saving Accounts
  int getNumberOfSavingAccounts() {
    int count = 0;
    for (auto subAcc : subAccounts) {
      if ((subAcc->getAccountNumber()).find("SAV") != string::npos) {
        count++;
      }
    }
    return count;
  }

  // get number of Checking Accounts
  int getNumberOfCheckingAccounts() {
    int count = 0;
    for (auto subAcc : subAccounts) {
      if ((subAcc->getAccountNumber()).find("CHK") != string::npos) {
        count++;
      }
    }
    return count;
  }

  // menu
  void menu() {
    char init_choice[100];
    int choice;
    do {
      cout << endl;
      cout << "Eligble servises for bank account: \"" << accountNumber << "\""
           << endl;
      cout << "  1. Open saving sub-account" << endl;   //+
      cout << "  2. Open checking sub-account" << endl; //+
      cout << "  3. Modify a sub-account" << endl;      //+
      cout << "  4. Close a sub-account" << endl;       //+
      cout << "  5. Detailed sub-accounts" << endl;     //+
      cout << "  6. Brief sub-accounts" << endl;        //+
      cout << "  7. Exit" << endl;                      //+

      cout << "Enter your choice: ";
      cin >> init_choice;
      choice = atoi(init_choice);

      switch (choice) {
      case 1:
        this->openSavingSubAccount();
        break;
      case 2:
        this->openCheckingSubAccount();
        break;
      case 3:
        this->modifySubAccount();
        break;
      case 4:
        this->closeSubAccount();
        break;
      case 5:
        this->printDetailed();
        break;
      case 6:
        this->printBrief();
        break;
      case 7:
        this->exit();
        break;
      default:
        cout << "### Invalid choice. Please try again." << endl;
        break;
      }
      cout << endl;
    } while (choice != 7);
  }

  // methods for Bank Account menu

  // open Saving Sub Account
  void openSavingSubAccount() {
    cout << endl;
    cout << "> Enter the initial balance: ";
    double balance;
    cin >> balance;

    if (getNumberOfSavingAccounts() == 0) {
      balance += 100;
    }
    SavingAccount *subAcc = new SavingAccount(balance);
    subAccounts.push_back(subAcc);
    cout << "| A new Saving Sub-Account " << subAcc->getAccountNumber()
         << " was successfully created." << endl;
  }

  // open Checking Sub Account
  void openCheckingSubAccount() {
    cout << endl;
    cout << "> Enter the initial balance: ";
    double balance;
    cin >> balance;
    cout << "> Enter the desired maximum capacity: ";
    double max_cap;
    cin >> max_cap;
    cout << "> Define initial state: (L - Locked, Ohterwise - Unlocked): ";
    string lock_status;
    cin >> lock_status;
    CheckingAccount *subAcc =
        new CheckingAccount(balance, max_cap, lock_status);
    subAccounts.push_back(subAcc);
    cout << "| A new Checking Sub-Account " << subAcc->getAccountNumber()
         << " was successfully created." << endl;
  }

  // modify Sub Account
  void modifySubAccount() {
    cout << endl;
    cout << "> Enter the Sub-Account number to modify: ";
    string account_number;
    cin >> account_number;
    auto it = find_if(subAccounts.begin(), subAccounts.end(),
                      [&](SubAccount *subAcc) {
                        return subAcc->getAccountNumber() == account_number;
                      });
    if (it == subAccounts.end()) {
      cout << "### Account not found." << endl;
      return;
    }
    (*it)->menu();
  }

  // close Sub Account
  void closeSubAccount() {
    cout << endl;
    cout << "> Enter Sub-Account number to be closed: ";
    string account_number;
    cin >> account_number;
    auto it = find_if(subAccounts.begin(), subAccounts.end(),
                      [&](SubAccount *subAcc) {
                        return subAcc->getAccountNumber() == account_number;
                      });
    if (it == subAccounts.end()) {
      cout << "### Sub-Account not found" << endl;
      return;
    }
    delete *it; // calls sub-account's destructor and releases the memory allocated for the object
    subAccounts.erase(it); // removes the pointer to sub-account object from 'subAccounts' collection
    cout << "| Sub-Account " << account_number << " was successfully closed."
         << endl;
  }

  // print Detailed
  void printDetailed() {
    cout << endl;
    sort(subAccounts.begin(), subAccounts.end(),
         [&](SubAccount *subAcc1, SubAccount *subAcc2) {
           return subAcc1->getBalance() > subAcc2->getBalance();
         });
    for (auto subAcc : subAccounts) {
      subAcc->printSubAccountInfo();
    }
    cout << endl;
  }

  // print Brief
  void printBrief() {
    cout << endl;
    cout << "| Aggregated balance of the bank account: " << accountNumber
         << " with " << subAccounts.size() << " Sub-Accounts is "
         << this->getBalance() << endl;
  }

  // exit
  void exit() {
    cout << endl;
    cout << "| End of servise for Bank Account: " << accountNumber << endl;
  }
};
