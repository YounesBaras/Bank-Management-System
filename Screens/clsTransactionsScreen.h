#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Utils/clsInputValidate.h"
#include <iomanip>

#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferRegisterScreen.h"

using namespace std;

class clsTransactionsScreen :protected clsScreen
{
private:
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,eShowTotalBalance = 3,
        eTransfer = 4,eTransferRegister = 5, eShowMainMenue = 6
    };

    static short ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::showTotalBalances();
    }

    static void _showTransferScreen() {
        clsTransferScreen::showTransferScreen();
    }

    static void _showTransferRegisterScreen() {
        clsTransferRegisterScreen::showTransferRegisterScreen();
    }

    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        system("cls");
        switch (TransactionsMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            _ShowDepositScreen();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            _ShowWithdrawScreen();
            break;
        }

        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            _ShowTotalBalancesScreen();
            
            break;
        }

        case enTransactionsMenueOptions::eTransfer: {
            _showTransferScreen();
            break;

        }
                                                  
        case enTransactionsMenueOptions::eTransferRegister: {
            _showTransferRegisterScreen();
            break;
        }

        }
    }

public:


    static void ShowTransactionsMenue(){
        while (true) {

            if (!clsScreen::CheckAccessRights(clsUser::pTranactions)) {
                return;
            }

            system("cls");
            _DrawScreenHeader("\t  Transactions Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Deposit.\n";
            cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
            cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
            cout << setw(37) << left << "" << "\t[4] Transfer.\n";
            cout << setw(37) << left << "" << "\t[5] Transfer Registers.\n";
            cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            enTransactionsMenueOptions option = (enTransactionsMenueOptions)ReadTransactionsMenueOption();

            if (option == eShowMainMenue)
                break;

            _PerformTransactionsMenueOption(option);

            cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions...\n";

            system("pause>0");
        }
    }

};
