#pragma once

#include <iostream>

using namespace std;

class clsPerson
{
private:
	string _firstName;
	string _lastName;
	string _email;
	string _phone;

public:
	clsPerson(string firstName, string lastName, string email, string phone) {
		_firstName = firstName;
		_lastName = lastName;
		_email = email;
		_phone = phone;
	}

	void setFirstName(string firstName){
		_firstName = firstName;
	}
	string firstName() {
		return _firstName;
	}

	void setLastName(string lastName) {
		_lastName = lastName;
	}
	string lastName() {
		return _lastName;
	}

	string fullName() {
		return _firstName + ' ' + _lastName;
	}

	void setEmail(string email) {
		_email = email;
	}
	string email() {
		return _email;
	}

	void setPhone(string phone) {
		_phone = phone;
	}
	string phone() {
		return _phone;
	}

};

