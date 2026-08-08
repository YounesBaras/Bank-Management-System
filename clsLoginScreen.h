#pragma once

#include <iostream>
#include "clsMainScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "global.h"

class clsLoginScreen : protected clsScreen
{
	static bool _login() {
		short trails = 3;
		bool loginFailed = false;
		do {

			if (loginFailed) {
				trails--;
				cout << "\nInvalid Username/Password\n";
				cout << "You have " << trails << " trails to login.\n";

				if (trails == 0) {
					cout << "\n\nYou are locked after 3 failed trails\n";
					return false;
				}
			}

			

			string username, password;

			cout << "\nEnter Username: ";
			cin >> username;

			cout << "\nEnter Password: ";
			cin >> password;

			currentUser = clsUser::Find(username, password);

			loginFailed = currentUser.IsEmpty();

		} while (loginFailed);
		currentUser.saveLogs();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:
	static bool showLoginScreen() {
		system("cls");
		clsScreen::_DrawScreenHeader("\t    Login Screen");
		return _login();
	
	}
};

