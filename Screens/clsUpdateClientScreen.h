#pragma once

#include <iostream>
#include "Core/clsBankClient.h"
#include "../Utils/clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateClientScreen :protected clsScreen
{

    static void _readClientInfo(clsBankClient& Client){
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

    static void _printClientCard(clsBankClient& client) {
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


    static void updateClient() {

        if (!clsScreen::CheckAccessRights(clsUser::pUpdateClients)) {
            return;
        }

        string accountNumber = "";

        cout << "\nPlease enter client account number: ";
        accountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::isClientExists(accountNumber)) {
            cout << "account number is not found, choose another one: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client1 = clsBankClient::find(accountNumber);
        _printClientCard(client1);

        char answer;
        cout << "\nAre you sure you want to update this client y/n? ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            cout << "Update client info:\n";
            cout << "-------------------\n";

            _readClientInfo(client1);

            switch (client1.save()) {

            case clsBankClient::enSaveResult::svFailedEmptyObject:
                cout << "\nSave failed the object is empty\n";
                break;

            case clsBankClient::enSaveResult::svSucceeded:
                cout << "\nSaved successfully\n";
                break;
            }
        }
    }

};

