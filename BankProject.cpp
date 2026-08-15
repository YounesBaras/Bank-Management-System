#include <iostream>
#include "Core/clsBankClient.h"
#include "Utils/clsInputValidate.h"
#include <iomanip>
#include "Utils/clsUtil.h"
#include "Screens/clsLoginScreen.h"
     
using namespace std;

int main()
{
    while (true) {
        if (!clsLoginScreen::showLoginScreen())
            break;
    }
}
