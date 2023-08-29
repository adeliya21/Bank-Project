#include <iostream>
#include <vector>
using namespace std;

// Base class for all sub-accounts
class SubAccount {

protected:
  string accountNumber;
  double balance;

public:
  // constructor of Sub-Accounts
  SubAccount(double balance) { this->balance = balance; }

  // destructor of Sub-Accounts
  ~SubAccount() {}

  // menu
  virtual void menu() {
    int choice;
    do {
      cout << "Eligble servises for Sub-Account: \"" << accountNumber << "\""
           << endl;
      cout << "  1. Deposit" << endl;  //+
      cout << "  2. Withdraw" << endl; //+
      cout << "  3. Exit" << endl;     //+

      cout << "Enter your choice: ";
      cin >> choice;

      switch (choice) {
      case 1:
        this->deposit();
        break;
      case 2:
        this->withdraw();
        break;
      case 3:
        this->exit();
        break;
      default:
        cout << "### Invalid choice. Please try again." << endl;
        break;
      }
      cout << endl;
    } while (choice != 3);
  }

  // methods used in Bank Account menu

  // get Balance
  double getBalance() { return balance; }

  // get accountNumber
  string getAccountNumber() { return accountNumber; }\


  // methods used in Sub-Account menu

  // deposit
  virtual void deposit() {
    cout << "> Enter the amount to deposit: ";
    double amount;
    cin >> amount;
    balance += amount;
    cout << "| Deposite was successful." << endl;
    cout << "| Current balance: " << balance << endl;
  }

  // withdraw
  virtual void withdraw() {
    cout << "> Enter the amount to withdraw: ";
    double amount;
    cin >> amount;
    if (balance - amount < 0) {
      cout << "### Error: insufficient funds" << endl;
      return;
    }
    balance -= amount;
    cout << "| Withdraw of was successful." << endl;
    cout << "| Current balance: " << balance << endl;
  }

  // print Sub-Account Info
  virtual void printSubAccountInfo() {
    cout << endl;
    cout << "| Sub-Account number: " << accountNumber << endl;
    cout << "| Balance: " << balance << endl;
  }

  // exit
  void exit() {
    cout << endl;
    cout << "| End of service for Sub-Account " << accountNumber << endl;
  }
};

// Saving Sub-Account class derived from Sub-Account class
class SavingAccount : public SubAccount {

private:
  static int accountNumberCounter;

public:
  // constructor of Saving-Account
  SavingAccount(double balance) : SubAccount(balance) {
    accountNumber = "SAV" + to_string(accountNumberCounter++);
  }

  // getter - method used in Bank menu
  static int getAccountNumberCounter() { return accountNumberCounter; }
};

// Checking Sub-Account class derived from Sub-Account class
class CheckingAccount : public SubAccount {

private:
  double max_capacity;
  bool is_locked;
  static int accountNumberCounter;

public:
  // constructor of Checking Account
  CheckingAccount(double balance, double max_cap, string lock_status)
      : SubAccount(balance) {
    this->max_capacity = max_cap;
    this->is_locked = (lock_status == "l" || lock_status == "L");
    accountNumber = "CHK" + to_string(accountNumberCounter++);
  }

  // getter - method used in Bank menu
  static int getAccountNumberCounter() { return accountNumberCounter; }

  // menu
  void menu() override {
    char init_choice[100];
    int choice;
    do {
      cout << "Eligble servises for Sub-Account: \"" << accountNumber << "\""
           << endl;
      cout << "  1. Deposit" << endl;            //+
      cout << "  2. Withdraw" << endl;           //+
      cout << "  3. Set max capacity" << endl;   //+
      cout << "  4. Lock sub-account" << endl;   //+
      cout << "  5. Unlock sub-account" << endl; //+
      cout << "  6. Exit" << endl;               //+

      cout << "Enter your choice: ";
      cin >> init_choice;
      choice = atoi(init_choice);

      switch (choice) {
      case 1:
        this->deposit();
        break;
      case 2:
        this->withdraw();
        break;
      case 3:
        this->setMaxCap();
        break;
      case 4:
        this->lock();
        break;
      case 5:
        this->unlock();
        break;
      case 6:
        this->exit();
        break;
      default:
        cout << "### Invalid choice. Please try again." << endl;
        break;
      }
      cout << endl;
    } while (choice != 6);
  }

  // methods used in Checking Account menu

  // deposit of Checking Account
  void deposit() override {
    if (is_locked) {
      cout << "### Error: the checking sub-account is locked" << endl;
      return;
    }

    cout << "> Enter the amount to deposit: ";
    double amount;
    cin >> amount;

    if (balance + amount > max_capacity) {
      cout << "### Error: deposit exceeds maximum capacity" << endl;
      return;
    }

    balance += amount;
    cout << "| Deposite of was successful." << endl;
    cout << "| Current balance: " << balance << endl;
  }

  // withdraw of Checking Account
  void withdraw() override {
    if (is_locked) {
      cout << "### Error: the checking sub-account is locked" << endl;
      return;
    }

    cout << "> Enter the amount to withdraw: ";
    double amount;
    cin >> amount;

    if (balance - amount < 0) {
      cout << "### Error: insufficient funds" << endl;
      return;
    }

    balance -= amount;
    cout << "| Withdraw was successful." << endl;
    cout << "| Current balance: " << balance << endl;
  }

  // set max capacity
  void setMaxCap() {
    if (is_locked) {
      cout << "### Error: the checking sub-account is locked" << endl;
      return;
    }
    
    cout << "> Enter desired max capacity: ";
    double max_cap;
    cin >> max_cap;

    if (max_cap < balance) {
      cout << "### Error: max capacity can not be less than current balance"
           << endl;
      return;
    }

    this->max_capacity = max_cap;
  }

  // lock
  void lock() {
    this->is_locked = true;
    cout << "| The sub-account " << accountNumber << " is locked now." << endl;
  }

  // unlock
  void unlock() {
    this->is_locked = false;
    cout << "| The sub-account " << accountNumber << " is unlocked now."
         << endl;
  }

  // methods used in Bank Account and Bank menu

  // print Info of Checking Account
  void printSubAccountInfo() override {
    SubAccount::printSubAccountInfo();
    cout << "| The maximum capacity: " << max_capacity << endl;
    if (is_locked == true) {
      cout << "| The sub-account is locked." << endl;
    } else {
      cout << "| The sub-account is unlocked." << endl;
    }
  }
};
