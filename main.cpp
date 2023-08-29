// Adeliia Salieva
#include <iostream>
#include <string>
using namespace std;
#include "Bank.h"

int startBankAccount = 10000;
int startSavingAccount = 1000;
int startCheckingAccount = 6000;

int BankAccount::accountNumberCounter = startBankAccount;
int SavingAccount::accountNumberCounter = startSavingAccount;
int CheckingAccount::accountNumberCounter = startCheckingAccount;

int main() {

  // initilize Bank
  cout << "> Enter the name of the bank: ";
  string name;
  cin >> name;
  cout << "> Enter adress of the bank: ";
  string address;
  cin >> address;
  cout << "> Enter adress of the bank: ";
  string wh;
  cin >> wh;
  Bank bank(name, address, wh);

  bank.menu();
}
