#pragma once

#include <iostream>
#include "Core/clsBankClient.h"
#include "clsScreen.h"
#include "../Utils/clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
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

    static void deleteClient() {

        if (!clsScreen::CheckAccessRights(clsUser::pDeleteClient)) {
            return;
        }

        string title = "\tDelete Client Screen";

        clsScreen::_DrawScreenHeader(title);

        string accountNumber = "";

        cout << "\nEnter account number to delete: ";
        accountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::isClientExists(accountNumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::find(accountNumber);

        _printClientCard(client);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char answer;
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            if (client.Delete())
                cout << "\nClient deleted successfully :-)\n";
            _printClientCard(client);

        }
    }

};

