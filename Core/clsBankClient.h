#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "..\Utils\clsString.h"
#include "global.h"

using namespace std;

class clsBankClient : public clsPerson
{
public:

    struct stTransferLogRecord
    {
        string dateTime;
        string sourceAccountNumber;
        string destinationAccountNumber;
        double amount;
        double srcBalanceAfter;
        double destBalanceAfter;
        string userName;
    };

private:

    enum enMode { emptyMode, updateMode, addNewMode };
    enMode _mode;

    string _accountNumber;
    string _pinCode;
    double _accountBalance;

    bool _markForDelete = false;

    static clsBankClient _convertDataLineToObject(
        string line,
        string separator = "#//#")
    {
        vector<string> vClientData =
            clsString::Split(line, separator);

        return clsBankClient(
            updateMode,
            vClientData[0],
            vClientData[1],
            vClientData[2],
            vClientData[3],
            vClientData[4],
            vClientData[5],
            stod(vClientData[6])
        );
    }

    static string _convertClientObjectToDataLine(
        clsBankClient client,
        string separator = "#//#")
    {
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

    static vector<clsBankClient> _loadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;

        fstream file;
        file.open("Data/clients.txt", ios::in);

        string line;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                if (!line.empty())
                    vClients.push_back(
                        _convertDataLineToObject(line)
                    );
            }

            file.close();
        }

        return vClients;
    }

    static void _addDataLineToFile(string line)
    {
        fstream file;
        file.open("Data/clients.txt", ios::app);

        if (file.is_open())
        {
            file << line << endl;
            file.close();
        }
    }

    static void _saveClientsDataToFile(
        vector<clsBankClient>& vClients)
    {
        fstream file;
        file.open("Data/clients.txt", ios::out);

        if (file.is_open())
        {
            for (clsBankClient& c : vClients)
            {
                if (!c._markForDelete)
                    file << _convertClientObjectToDataLine(c)
                    << endl;
            }

            file.close();
        }
    }

    void _update()
    {
        vector<clsBankClient> vClients =
            _loadClientsDataFromFile();

        for (clsBankClient& c : vClients)
        {
            if (c.accountNumber() == accountNumber())
            {
                c = *this;
                break;
            }
        }

        _saveClientsDataToFile(vClients);
    }

    void _addNew()
    {
        _addDataLineToFile(
            _convertClientObjectToDataLine(*this)
        );
    }

    static clsBankClient _getEmptyClientObject()
    {
        return clsBankClient(
            emptyMode,
            "",
            "",
            "",
            "",
            "",
            "",
            0
        );
    }

    static string _getTransferRegisterLine(double amount,clsBankClient& clientFrom,
        clsBankClient& clientTo,string separator = "#//#")
    {
        string line = "";

        line += clsDate::getSystemDateTimeString() + separator;
        line += clientFrom.accountNumber() + separator;
        line += clientTo.accountNumber() + separator;
        line += to_string(amount) + separator;
        line += to_string(clientFrom.accountBalance()) + separator;
        line += to_string(clientTo.accountBalance()) + separator;
        line += currentUser.UserName;

        return line;
    }

    static stTransferLogRecord _convertTransferLineToRecord(
        string line,
        string separator = "#//#")
    {
        vector<string> vData =
            clsString::Split(line, separator);

        stTransferLogRecord record;

        record.dateTime = vData[0];
        record.sourceAccountNumber = vData[1];
        record.destinationAccountNumber = vData[2];
        record.amount = stod(vData[3]);
        record.srcBalanceAfter = stod(vData[4]);
        record.destBalanceAfter = stod(vData[5]);
        record.userName = vData[6];

        return record;
    }

    static vector<stTransferLogRecord>
        _loadTransfersLogDataFromFile()
    {
        vector<stTransferLogRecord> vTransfers;

        fstream file;
        file.open(
            "Data/transferRegister.txt",
            ios::in
        );

        if (file.is_open())
        {
            string line;

            while (getline(file, line))
            {
                if (!line.empty())
                {
                    vTransfers.push_back(
                        _convertTransferLineToRecord(line)
                    );
                }
            }

            file.close();
        }

        return vTransfers;
    }

public:

    clsBankClient(
        enMode mode,
        string firstName,
        string lastName,
        string email,
        string phone,
        string accountNumber,
        string pinCode,
        double accountBalance)
        : clsPerson(firstName, lastName, email, phone)
    {
        _mode = mode;
        _accountNumber = accountNumber;
        _pinCode = pinCode;
        _accountBalance = accountBalance;
    }

    static clsBankClient getAddNewClientObject(
        string accountNumber)
    {
        return clsBankClient(
            addNewMode,
            "",
            "",
            "",
            "",
            accountNumber,
            "",
            0
        );
    }

    bool isEmpty()
    {
        return (_mode == emptyMode);
    }

    string accountNumber()
    {
        return _accountNumber;
    }

    string pinCode()
    {
        return _pinCode;
    }

    void setPinCode(string pinCode)
    {
        _pinCode = pinCode;
    }

    double accountBalance()
    {
        return _accountBalance;
    }

    void setAccountBalance(double accountBalance)
    {
        _accountBalance = accountBalance;
    }

    static clsBankClient find(string accountNumber)
    {
        fstream file;
        file.open("Data/clients.txt", ios::in);

        if (file.is_open())
        {
            string line;

            while (getline(file, line))
            {
                if (line.empty())
                    continue;

                clsBankClient client =
                    _convertDataLineToObject(line);

                if (client.accountNumber() == accountNumber)
                {
                    file.close();
                    return client;
                }
            }

            file.close();
        }

        return _getEmptyClientObject();
    }

    static clsBankClient find(
        string accountNumber,
        string pinCode)
    {
        fstream file;
        file.open("Data/clients.txt", ios::in);

        if (file.is_open())
        {
            string line;

            while (getline(file, line))
            {
                if (line.empty())
                    continue;

                clsBankClient client =
                    _convertDataLineToObject(line);

                if (client.accountNumber() == accountNumber &&
                    client.pinCode() == pinCode)
                {
                    file.close();
                    return client;
                }
            }

            file.close();
        }

        return _getEmptyClientObject();
    }

    static bool isClientExists(string accountNumber)
    {
        clsBankClient client = find(accountNumber);

        return (!client.isEmpty());
    }

    enum enSaveResult
    {
        svFailedEmptyObject,
        svSucceeded,
        svFailedAccountNumberExist
    };

    enSaveResult save()
    {
        switch (_mode)
        {
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

        return svFailedEmptyObject;
    }

    bool Delete()
    {
        vector<clsBankClient> vClients =
            _loadClientsDataFromFile();

        for (clsBankClient& c : vClients)
        {
            if (c.accountNumber() == _accountNumber)
            {
                c._markForDelete = true;
                break;
            }
        }

        _saveClientsDataToFile(vClients);

        *this = _getEmptyClientObject();

        return true;
    }

    static vector<clsBankClient> getClientsList()
    {
        return _loadClientsDataFromFile();
    }

    static double getTotalBalances()
    {
        vector<clsBankClient> vClients =
            _loadClientsDataFromFile();

        double total = 0;

        for (clsBankClient& c : vClients)
        {
            total += c.accountBalance();
        }

        return total;
    }

    void deposit(double amount)
    {
        _accountBalance += amount;
        save();
    }

    bool withdraw(double amount)
    {
        if (amount > _accountBalance)
            return false;

        _accountBalance -= amount;
        save();

        return true;
    }

    static void saveTransferRegister(
        double& amount,
        clsBankClient& clientFrom,
        clsBankClient& clientTo)
    {
        fstream file;

        file.open(
            "Data/transferRegister.txt",
            ios::out | ios::app
        );

        if (file.is_open())
        {
            string line =
                _getTransferRegisterLine(
                    amount,
                    clientFrom,
                    clientTo
                );

            file << line << endl;

            file.close();
        }
        else
        {
            cout << "\n\nERROR: FAILED TO OPEN "
                << "\"Data/transferRegister.txt\"\n\n";
        }
    }

    static bool transfer(
        double& amount,
        clsBankClient& clientFrom,
        clsBankClient& clientTo)
    {
        if (!clientFrom.withdraw(amount))
            return false;

        clientTo.deposit(amount);

        saveTransferRegister(
            amount,
            clientFrom,
            clientTo
        );

        return true;
    }

    static vector<stTransferLogRecord>
        getTransfersLogList()
    {
        return _loadTransfersLogDataFromFile();
    }
};