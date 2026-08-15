#pragma once

#include <iostream>
#include "Core/clsBankClient.h"
#include "../Utils/clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
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

    static void findClient() {

        if (!clsScreen::CheckAccessRights(clsUser::pFindClient)) {
            return;
        }

        clsScreen::_DrawScreenHeader("\tFind Client Screen");

        string accountNumber = "";

        cout << "Enter account number to find: ";
        accountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::isClientExists(accountNumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::find(accountNumber);

        cout << "\nClient was found :-)\n";

        _printClientCard(client);

    }

};

