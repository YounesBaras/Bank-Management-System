#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "global.h"

using namespace std;

class clsBankClient : public clsPerson
{
	enum enMode { emptyMode, updateMode, addNewMode };
	enMode _mode;

	string _accountNumber;
	string _pinCode;
	double _accountBalance;

	bool _markForDelete = false;

	static clsBankClient _convertDataLineToObject(string line, string separator = "#//#") {
		vector <string> vClientData = clsString::Split(line, separator);

		return clsBankClient(updateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _convertClientObjectToDataLine(clsBankClient client, string separator = "#//#") {
		string line = "";
		line += client.firstName() + separator;
		line += client.lastName() + separator;
		line += client.email() + separator;
		line += client.phone() + separator;
		line += client.accountNumber() + separator;
		line += client.pinCode() + separator;
		line += to_string(client.accountBalance());
		return line;
	}

	static vector <clsBankClient> _loadClientsDataFromFile(){
		vector <clsBankClient> vClients;

		fstream file;
		file.open("Clients.txt", ios::in);

		string line;

		if (file.is_open()) {
			while (getline(file, line)) {
				vClients.push_back(_convertDataLineToObject(line));
			}
			file.close();
		}

		return vClients;
	}

	static void _addDataLineToFile(string line) {
		fstream file;
		file.open("Clients.txt", ios::app);

		if (file.is_open()) {

			file << line << endl;

			file.close();
		}

	}

	static void _saveClientsDataToFile(vector <clsBankClient>& vClients) {
		fstream file;
		file.open("Clients.txt", ios::out);

		if (file.is_open()) {

			for (clsBankClient& c : vClients) {
				if(!c._markForDelete)
					file << _convertClientObjectToDataLine(c) << endl;
			}
			file.close();
		}
	}

	void _update() {
		vector <clsBankClient> vClients;
		vClients = _loadClientsDataFromFile();

		for (clsBankClient& c : vClients) {
			if (c.accountNumber() == accountNumber()) {
				c = *this;
				break;
			}
		}
		_saveClientsDataToFile(vClients);
	}

	void _addNew() {
		_addDataLineToFile(_convertClientObjectToDataLine(*this));
	}

	static clsBankClient _getEmptyClientObject() {
		return clsBankClient(emptyMode, "", "", "", "", "", "", 0);
	}

	static string _getTransferRegisterLine(double amount, clsBankClient& clientFrom, clsBankClient& clientTo, string seperator = "#//#") {
		string line = "";
		line += clsDate::getSystemDateTimeString() + seperator;
		line += clientFrom.accountNumber() + seperator;
		line += clientTo.accountNumber() + seperator;
		line += to_string(amount) + seperator;
		line += to_string(clientFrom.accountBalance()) + seperator;
		line += to_string(clientTo.accountBalance()) + seperator;
		line += currentUser.UserName;
		return line;
	}

public:
	clsBankClient(enMode mode, string firstName, string lastName, string email,
		string phone, string accountNumber, string pinCode, double accountBalance) : clsPerson(firstName, lastName, email, phone) 
	{
		_mode = mode;
		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_accountBalance = accountBalance;

	}

	static clsBankClient getAddNewClientObject(string accountNumber) {
		return clsBankClient(addNewMode, "", "", "", "", accountNumber, "", 0);
	}

	bool isEmpty() {
		return (_mode == emptyMode);
	}

	string accountNumber() {
		return _accountNumber;
	}

	string pinCode() {
		return _pinCode;
	}

	void setPinCode(string pinCode) {
		_pinCode = pinCode;
	}

	double accountBalance() {
		return _accountBalance;
	}

	void setAccountBalance(double accountBalance) {
		_accountBalance = accountBalance;
	}

	static clsBankClient find(string accountNumber) {
		fstream file;
		file.open("clients.txt", ios::in);

		if (file.is_open()) {

			string line;

			while (getline(file, line)) {

				clsBankClient client = _convertDataLineToObject(line);

				if (client.accountNumber() == accountNumber) {
					file.close();
					return client;
				}

			}

			file.close();
		}
		return _getEmptyClientObject();
	}

	static clsBankClient find(string accountNumber, string pinCode) {
		fstream file;
		file.open("clients.txt", ios::in);

		if (file.is_open()) {

			string line;

			while (getline(file, line)) {

				clsBankClient client = _convertDataLineToObject(line);

				if (client.accountNumber() == accountNumber && client.pinCode() == pinCode) {
					file.close();
					return client;
				}

			}

			file.close();
		}
		return _getEmptyClientObject();
	}

	static bool isClientExists(string accountNumber) {
		clsBankClient client = find(accountNumber);
		return (!client.isEmpty());
	}

	enum enSaveResult { svFailedEmptyObject, svSucceeded, svFailedAccountNumberExist };

	enSaveResult save() {

		switch (_mode) {

		case updateMode:
			_update();
			return enSaveResult::svSucceeded;

		case emptyMode:
			return enSaveResult::svFailedEmptyObject;

		case addNewMode:
			if (isClientExists(accountNumber()))
				return svFailedAccountNumberExist;
			_addNew();
			_mode = updateMode;
			return svSucceeded;

		}

	}

	bool Delete() {
		vector <clsBankClient> vClients = _loadClientsDataFromFile();

		for (clsBankClient& c : vClients) {

			if (c.accountNumber() == _accountNumber) {
				c._markForDelete = true;
				break;
			}

		}

		_saveClientsDataToFile(vClients);
		*this = _getEmptyClientObject();

		return true;
	}

	static vector <clsBankClient> GetClientsList() {
		return _loadClientsDataFromFile();
	}

	static double getTotalBalances() {
		vector <clsBankClient> vClients = _loadClientsDataFromFile();

		double total = 0;

		for (clsBankClient& c : vClients) {

			total += c.accountBalance();

		}
		return total;
	}

	void deposit(double amount) {
		_accountBalance += amount;
		save();
	}

	bool withdraw(double amount) {
		if (amount > _accountBalance)
			return false;
		else {
			_accountBalance -= amount;
			save();
			return true;
		}
	}

	static void saveTransfareRegister(double &amount, clsBankClient& clientFrom, clsBankClient& clientTo){
		fstream file;
		file.open("transferRegister.txt", ios::out | ios::app);

		if (file.is_open()) {
			string line = _getTransferRegisterLine(amount, clientFrom, clientTo);
			file << line << endl;
			file.close();
		}
		else
			cout << "\n\nERROR: FAILED TO OPEN \"transferRegister.txt\"\n\n";

	}

	static bool transfer(double &amount, clsBankClient &clientFrom, clsBankClient& clientTo) {
		if (!clientFrom.withdraw(amount))
			return false;
		clientTo.deposit(amount);

		saveTransfareRegister(amount, clientFrom, clientTo);

		return true;
	}

};

