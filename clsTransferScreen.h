#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsTransferScreen : protected clsScreen
{

	static void _printClientCard(clsBankClient & client) {
		cout << "\nClient Card: ";
		cout << "\n--------------------\n";
		cout << "Full Name  : " << client.fullName();
		cout << "\nAcc. Number: " << client.accountNumber();
		cout << "\nBalance    : " << to_string(client.accountBalance());
		cout << "\n--------------------\n";
	}

public:

	static void showTransferScreen() {
		clsScreen::_DrawScreenHeader("\t Transfer Screen");

		string firstAccountNumber;
		cout << "\nPlease enter account number to transfer from: ";
		firstAccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::isClientExists(firstAccountNumber)) {
			cout << "\nAccount number is not exists, please enter another one: ";
			firstAccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client1 = clsBankClient::find(firstAccountNumber);
		_printClientCard(client1);

		string secondAccountNumber;
		cout << "\nPlease enter account number to transfer to: ";
		secondAccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::isClientExists(secondAccountNumber) || firstAccountNumber == secondAccountNumber) {
			if (firstAccountNumber == secondAccountNumber)
				cout << "\nYou cant transfer from and to same client, please enter another account number: ";
			else
				cout << "\nAccount number is not exists, please enter another one: ";
			secondAccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client2 = clsBankClient::find(secondAccountNumber);
		_printClientCard(client2);

		double amount;
		cout << "\nEnter transfer amount: ";
		amount = clsInputValidate::ReadDblNumber();

		while (amount > client1.accountBalance()) {
			cout << "\nAmount Exceeds the availabel balance, please enter another amount: ";
			amount = clsInputValidate::ReadDblNumber();
		}

		char answer = 'n';
		cout << "Are you sure you want to perform this operation? y/n? ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {
			if (!clsBankClient::transfer(amount, client1, client2)) {
				cout << "Fail to withdraw from " << client1.fullName() << endl;
				return;
			}
			
			cout << "\nTransfer done successfully\n";

			_printClientCard(client1);
			_printClientCard(client2);

		}
	}
};

