#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>

#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLogRegisterScreen.h"
#include "global.h"

using namespace std;

class clsMainScreen :protected clsScreen
{


private:
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLogRegister = 8, eLogout = 9
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 9]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 9, "Enter Number between 1 to 9? ");
        return Choice;
    }

    static void _ShowAllClientsScreen()
    {
        //cout << "\nClient List Screen Will be here...\n";

        clsClientListScreen::showClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        //cout << "\nAdd New Client Screen Will be here...\n";
        
        clsAddNewClientScreen::addNewClient();

    }

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::deleteClient();
    }

    static void _ShowUpdateClientScreen(){
        //cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::updateClient();
    }

    static void _ShowFindClientScreen()
    {
        //cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::findClient();
    }

    static void _ShowTransactionsMenue()
    {
        //cout << "\nTransactions Menue Will be here...\n";
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::showManageUsersMenue();

    }

    static void _ShowLogRegisterMenue() {
        clsLogRegisterScreen::showLogRegisterScreen();
    }

    static void _logout() {
        currentUser = clsUser::Find("");
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            break;

        case enMainMenueOptions::eLogRegister:
            system("cls");
            _ShowLogRegisterMenue();
            break;

        case enMainMenueOptions::eLogout:
            system("cls");
            _logout();

            break;
        }

    }



public:


    static void ShowMainMenue()
    {
        while (true) {
            system("cls");
            _DrawScreenHeader("\t\tMain Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
            cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
            cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
            cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
            cout << setw(37) << left << "" << "\t[5] Find Client.\n";
            cout << setw(37) << left << "" << "\t[6] Transactions.\n";
            cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
            cout << setw(37) << left << "" << "\t[8] Log Registers.\n";
            cout << setw(37) << left << "" << "\t[9] Logout.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            enMainMenueOptions option = (enMainMenueOptions)_ReadMainMenueOption();

            _PerfromMainMenueOption(option);

            if (option == eLogout)
                break;

            cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

            system("pause>0");
        }
    }

};

