/*
	User.h
	This header file defines all of the User object functions.
	This also defines the following variables:
	isAdmin, isGuest, statusLevel, firstName, lastName, username, password, and userID
*/

#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User {
protected:
	string* firstName;
	string* lastName;
	string* address;
	string* phoneNum;
	string* email;
	bool isAdmin;
public:
	// Constructors
	User(const string& fName, const string& lName, const string& address, const string& phoneNum, const string& email);
	User();
	~User();
	User(const User& newU);

	// Mutators
	void setFirstName(string firstName);
	void setLastName(string lastName);
	void setAddress(string a);
	void setPhoneNumber(string p);
	void setEmail(string e);

	// Accessors 
	string& getFirstName()const;
	string& getLastName()const;
	string& getAddress()const;
	string& getPhoneNumber()const;
	string& getEmail()const;
	bool getAdminStatus() const {};
};

#endif // USER_H