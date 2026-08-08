#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
    static void _readClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.setFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        Client.setLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.setEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.setPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.setPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.setAccountBalance(clsInputValidate::ReadDblNumber());
    }

    static void _printClientCard(clsBankClient &client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.firstName();
        cout << "\nLastName    : " << client.lastName();
        cout << "\nFull Name   : " << client.fullName();
        cout << "\nEmail       : " << client.email();
        cout << "\nPhone       : " << client.phone();
        cout << "\nAcc. Number : " << client.accountNumber();
        cout << "\nPassword    : " << client.pinCode();
        cout << "\nBalance     : " << client.accountBalance();
        cout << "\n___________________\n";

    }

public:

    static void addNewClient() {

        if (!clsScreen::CheckAccessRights(clsUser::pAddNewClient)) {
            return;
        }

        string title = "\tAdd New Client Screen";

        clsScreen::_DrawScreenHeader(title);

        string accountNumber = "";

        cout << "\nPlease enter account number: ";
        accountNumber = clsInputValidate::ReadString();

        while (clsBankClient::isClientExists(accountNumber)) {
            cout << "\nAccount number is already used, choose another one: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient newClient = clsBankClient::getAddNewClientObject(accountNumber);

        _readClientInfo(newClient);

        clsBankClient::enSaveResult saveResult;

        saveResult = newClient.save();

        switch (saveResult) {
        case clsBankClient::svFailedAccountNumberExist:
            cout << "\nSave faild account number already exists";
            break;
        case clsBankClient::svFailedEmptyObject:
            cout << "\nSave faild account number is empty";
            break;
        case clsBankClient::svSucceeded:
            cout << "\nClient added succesfully";
            _printClientCard(newClient);
            break;
        }

    }

};

