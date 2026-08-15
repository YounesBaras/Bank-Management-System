#pragma once

#include <iostream>
#include "clsScreen.h"
#include "Core/clsBankClient.h"
#include "../Utils/clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
{

private:

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

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }


public:

    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();


        while (!clsBankClient::isClientExists(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client1 = clsBankClient::find(AccountNumber);
        _printClientCard(Client1);

        double Amount = 0;
        cout << "\nPlease enter withdraw amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client1.withdraw(Amount)) {
                cout << "\nAmount Withdrawed Successfully.\n";
                cout << "\nNew Balance Is: " << Client1.accountBalance();
            }
            else {
                cout << "\nCannot withdraw, Insuffeciant balance!\n";

                cout << "\nAmount to withdraw is: " << Amount;
                cout << "\nYour balance is: " << Client1.accountBalance() << endl;
            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }

};

