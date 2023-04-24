#pragma once
#include <iostream>
#include "vector"
#include <string>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;

class people {
public:
	char name[20]; //Users' name is mostly consist of 20 characters
	char number[20]; //the account
	char password[20];

	void password_check(string str_test, int digit,char str[20]);
};
class account;

account* find_vec(char* number);
//void tsave();
//void tload();
class account :people {  //"Account" class include class people
	char category[20];
	float balance;
	float loan_amount;
	float loan_quota_left;
	float loan_rate;

public:
	account();
	account(
		// Decalration in "people"
		//"name0" at first changes to "m_name"
		char* m_name,
		char* m_number,
		char* m_password,

		// Declaration in "account"
		char* m_category,
		float m_balance,
		float m_loan_amount,
		float m_loan_quota_left,
		float m_loan_rate);

	// Get loan amount
	float get_loan_amount();

	// People's number
	char* get_number();

    // Passowrd
	void set_password(char* pass);
	char* get_passsword();

	// Balance
	float get_balance();
	void set_balance(float temp);
	void add_balance(float temp);
	void sub_balance(float temp);

	// Services
	void cmd_users();
	void inquiry();
	void desposit();
	void withdraw();
	void transfer();
	void loan();
	void repayment();
	void change_password();
	void display();
	void back_users();

	void save(FILE* fp);

};

///////////////////////////////////////////////////
//Functions about manager class are mostly in "bank_manager.cpp"
class manager :people {
	float borrowable_amount;
	float total_deposits;
	float loan_interest_personal;
	float loan_interest_enterprise;

	float person_rate;
	float enterprise_rate;
public:
	manager();
	//manager* find_vec_manager(char* number);
	// from "people"
	char* get_number();
	char* get_name();
	char* get_passsword();

	// The cmd for manager interface
	void cmd_manager();

	void create_account();
	void check_borrowable();
	void check_deposits();
	void check_customer();
	void Reset_password();
	void print();

	float get_barrowable();
	float get_total_deposits();
	float get_total_interstperson();
	float get_loan_interest();
	void back_manager(); //quit or not
	void ttsave();
};
#pragma once
