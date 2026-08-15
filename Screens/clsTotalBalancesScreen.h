#pragma once

#include <iostream>
#include <iomanip>
#include "Core/clsBankClient.h"
#include "../Utils/clsUtil.h"
#include "clsScreen.h"

class clsTotalBalancesScreen : protected clsScreen
{
    static void printClientRecordBalanceLine(clsBankClient Client)
    {

        cout << "| " << setw(15) << left << Client.accountNumber();
        cout << "| " << setw(40) << left << Client.fullName();
        cout << "| " << setw(12) << left << Client.accountBalance();

    }

public:

    static void showTotalBalances() {
        vector <clsBankClient> vClients = clsBankClient::getClientsList();

        string subtitle = "\t    (" + to_string(vClients.size()) + ") Client(s)";

        clsScreen::_DrawScreenHeader("\t Total Balances Screen", subtitle);

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        double TotalBalances = clsBankClient::getTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {
                printClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
        cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";
    }


};

