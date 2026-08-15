#pragma once

#include <iostream>
#include "clsScreen.h"
#include "Core/clsBankClient.h"
#include <iomanip>

using namespace std;

class clsClientListScreen : protected clsScreen
{
    static void _printClientRecordLine(clsBankClient Client)
    {

        cout << "| " << setw(15) << left << Client.accountNumber();
        cout << "| " << setw(20) << left << Client.fullName();
        cout << "| " << setw(12) << left << Client.phone();
        cout << "| " << setw(20) << left << Client.email();
        cout << "| " << setw(10) << left << Client.pinCode();
        cout << "| " << setw(12) << left << Client.accountBalance();

    }

public:

    static void showClientsList(){
        
        if (!clsScreen::CheckAccessRights(clsUser::pListClients)) {
            return;
        }

        vector <clsBankClient> vClients = clsBankClient::getClientsList();

        string title = "\t  Clients list screen";
        string subtitle = "\t  (" + to_string(vClients.size()) + ") Clients";

        clsScreen::_DrawScreenHeader(title, subtitle);

        cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {

                _printClientRecordLine(Client);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

