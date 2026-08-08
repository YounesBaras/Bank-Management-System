#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"


class clsUsersListScreen : protected clsScreen
{
    static void _printUserRecordLine(clsUser User){

        cout << setw(8) << left << "" << "| " << setw(12) << left << User.UserName;
        cout << "| " << setw(25) << left << User.fullName();
        cout << "| " << setw(12) << left << User.phone();
        cout << "| " << setw(20) << left << User.email();
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;

    }

public:

    static void showUsersListScreen() {

        vector <clsUser> vUsers = clsUser::GetUsersList();

        string title = "\tUsers List";
        string subtitle = "\t  (" + to_string(vUsers.size()) + ") Users(s)";

        clsScreen::_DrawScreenHeader(title, subtitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else {

            for (const clsUser& u : vUsers) {
                _printUserRecordLine(u);
                cout << '\n';
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

    }
};

