#include "bank.h"
int cur_id = 1001;
extern vector<account*> vecs; //Can be used in all files

////////////////////////////
//↓ For costomer

account* find_vec(char* number) {  // Callout the information
	for (int i = 0; i < vecs.size(); i++) {
		if (strcmp(vecs[i]->get_number(), number) == 0) {
			return (vecs[i]);
		}
	}
	return NULL;
}

void tsave() { //改这里
	FILE* fp = fopen("account.txt", "w+");
	fprintf(fp, "%d\n", vecs.size());
	for (int i = 0; i < vecs.size(); i++) {
		vecs[i]->save(fp);
	}
	fclose(fp);
}

// Creative the account
account::account() {
	cout << "Please input name:";
	cin >> name;
	cout << "Your account number is:";
	sprintf(number, "%d", 1001+vecs.size());
	cout << number << endl;
	cout << "Please input your account password:";
	string password_test;
	cin >> password_test;
	password_check(password_test, 20, password);
	int category_choose;
		cout << "Please choose a type of category:" << endl;
		cout << "1.enterprise" << endl; //Back to Operation menu
		cout << "2.personal" << endl; //Terminate the program
		cin >> category_choose;
		if (category_choose == 1){
			string category_insert = "enterprise"; // add as "enterprise"
		    int i = 0;
	        for(i = 0 ;i < category_insert.length();i++){
				category[i] = category_insert[i];
	       }
	       category[i] = '\0';
		}
		if (category_choose == 2){
			string category_insert = "personal";  // add as "personal"
		    int i = 0;
	        for(i = 0 ;i < category_insert.length();i++){ 
                 category[i] = category_insert[i];
	       }
	       category[i] = '\0';
		}

	if (strcmp(category, "enterprise") == 0) {
		loan_rate = 0.05;
		loan_quota_left = 50000;
	}
	else {
		loan_rate = 0.03;
		loan_quota_left = 30000;
	}
	cout << "Please input the inquiry:" << endl;
	char str[50];
	cin>>str;
	balance=atof(str);
	//cin >> balance;
	loan_amount = 0;
	cout << "Create success!" << endl;
}

account::account(
	// Decaration in people
	char* m_number,
	char* m_name,
	char* m_password,
	// Declaration in account
	char* m_category,
	float m_loan_amount,
	float m_loan_quota_left,
	float m_loan_rate,
	float m_balance)
{
	strcpy(name, m_name);
	strcpy(number, m_number);
	strcpy(password, m_password);
	strcpy(category, m_category);
	balance = m_balance;
	loan_amount = m_loan_amount;
	loan_quota_left = m_loan_quota_left;
	loan_rate = m_loan_rate;
}
//get information
float account::get_loan_amount() {
	return loan_amount;
}
char* account::get_number() {
	return number;
}
//About password
void account::set_password(char* pass) {
	strcpy(password, pass);
}
char* account::get_passsword() {
	return password;
}
// about balance
float account::get_balance() {
	return (balance);
}
void account::set_balance(float temp) {
	balance = temp;
}
void account::add_balance(float temp) {
	balance += temp;
}
void account::sub_balance(float temp) {
	balance -= temp;
}
//////////////////////////
//interface for users
void account::cmd_users() {
	int cmd;
	while (1) {
		system("cls");
		cout << "Users:" << endl;
		cout << "1.Inquiry" << endl;
		cout << "2.Desposit" << endl;
		cout << "3.Withdraw" << endl;
		cout << "4.Transfer" << endl;
		cout << "5.Loan" << endl;
		cout << "6.Repay" << endl;
		cout << "7.Change password" << endl;
		cout << "8.Quit" << endl;
		cout << "Please input your choice:" << endl;
		cin >> cmd;
		if (cmd == 1)this->inquiry();
		if (cmd == 2)this->desposit();
		if (cmd == 3)this->withdraw();
		if (cmd == 4)this->transfer();
		if (cmd == 5)this->loan();
		if (cmd == 6)this->repayment();
		if (cmd == 7)this->change_password();
		if (cmd == 8)exit(0);
		if (cmd < 1 || cmd > 8){cout << "Input out of range!"<< endl;}this->back_users(); //when cmd incorrect
		tsave();
		system("pause");
		back_users(); //After each operation, can choose leave or not
	}
}

// Check the inquiry
// when cmd == 1
void account::inquiry() {
	cout << "Output the balance as following" << endl;
	cout << name << "," << "your balance is " << balance << endl;
	tsave();
}

// Check the desposit
// when cmd == 2
void account::desposit() {
	cout << "Input how much money you want to deposit" << endl;
	cout << "please input the amount to save:";
	char str[50];
	cin >> str;
	float temp = atof(str);
	if (temp < 0) {
		cout << "desposit fail " << endl;
	}
	else {
		balance += temp;
		cout << "Dear "<< name << ",your balance has been updated to " << balance << endl;
	}
	tsave();
}

// Withdrawing
// when cmd == 3
void account::withdraw() {
	cout << "Input the amount you want to withdraw" << endl;
	cout << "please input the amount to withdraw:" << endl;
	float temp;
	cin >> temp;
	if (temp<0 || temp>balance) {
		cout << "withdraw fail " << endl;
	}
	else {
		balance -= temp;
		cout << "Dear "<<name<<", your balance has been updated to " << balance << endl;
	}
	tsave();
}

// Transfer to another account
// when cmd == 4
void account::transfer() {

	cout << "Input the target account number";
	char temp1[50];
	cin >> temp1;
	account* rev = find_vec(temp1);
	if (rev == NULL) {
		cout << "transfer fail" << endl;
		return;
	}
	float temp;
	cout << "金额:";
	cin >> temp;
	if (temp <= 0 || this->get_balance() - temp <= 0) {
		cout << "transfer fail" << endl;
		return;
	}
	else {
		rev->add_balance(temp);
		this->sub_balance(temp);
	}
	tsave();
}

// Loan from bank
// when cmd == 5
void account::loan() {
	cout << "Please input the amount to loan:";
	float temp;
	cin >> temp;
	float temp1 = loan_quota_left;
	if (temp <= 0 || temp > loan_quota_left) {
		cout << "loan fail" << endl;
		return;
	}
	else {
		loan_quota_left -= temp;
		balance += temp;
		loan_amount += temp;
		cout << "your withdrawable amount now "<< loan_amount << endl;
		cout << "your loan quota left is " << this->loan_quota_left << endl;
	}
	tsave();
}

// Check loan_amount
// when cmd == 6
void account::repayment() {
	float temp1 = balance;
	float temp = loan_amount;
	if (temp1 < (temp*(1 + loan_rate))) {
		cout << "repayment fail" << endl;
		return;
	}
	else {
		temp1 -= temp * (1 + loan_rate);
		balance = temp1;
		temp1 = 0;
		loan_amount = temp1;
		temp1 = loan_quota_left + temp;
		loan_quota_left = temp1;
		cout << "cheers! your loan amount now is " << temp1 << ", you loan quota now is " << loan_quota_left << endl;
		cout << "your withdrawable amount has been updated to " << balance << endl;
	}
	tsave();
}

// Change password
// when cmd == 7
void account::change_password() {
	cout << "please input your original password:" << endl;
	cout << "the length of password should be under 20" << endl;
	char str[20];
	string str_test;
	char str1[20];
	string str1_test;
	cin >> str_test;
	password_check(str_test, 20, str);
	if (strcmp(str, password) != 0) {
		cout << "change_password fail" << endl;
		return;
	}
	else {
		cout << "please input your new password:";
		cin >> str_test;
		password_check(str_test, 20, str);
		cout << "please input your new password again:";
		cin >> str1_test;
		password_check(str1_test, 20, str1);
		if (strcmp(str, str1) == 0) {
			strcpy(password, str);
			cout << "update password successfully" << endl;
		}
		else {
			cout << "change password failed" << endl;
		}
	}
	tsave();
}

//display
void account::display() {
	cout << number << " " << name << " " << balance << " " << this->category << " " << loan_amount << " " << loan_quota_left <<" "<<balance - loan_amount << endl;
}

// save the information
void account::save(FILE* fp) {
	//printf("%s %s %s %s %f %f %f %f\n", name, number, password, category, loan_amount, loan_quota_left, loan_rate, balance);
	char str[4][50];
	sprintf(str[0],"%f", loan_amount);
	sprintf(str[1], "%f", loan_quota_left);
	sprintf(str[2], "%f", loan_rate);
	sprintf(str[3], "%f", balance);
	fprintf(fp, "%s %s %s %s %s %s %s %s\n", number, name, password, category, str[0], str[1], str[2], str[3]);

	return;
}

void account::back_users(){
	int cmd = 0;
	while(1){
		cout << "You want to back to the menu or quit?" << endl;
		cout << "1.Continue" << endl; //Back to Operation menu
		cout << "2.Quit" << endl; //Terminate the program
		cin >> cmd;
		if (cmd == 1){cmd_users();}
		if (cmd == 2){exit(0);} //end the programme directly
		if (cmd != 1 && cmd != 2){cout << "Input out of range!"<< endl;}this->back_users();
		//↑ the input number incorrect
		system("pause");
		}
}

void people::password_check(string str_test, int digit,char str[20]){
		if(str_test.length() > digit){
		int cmd_choose;
		while(1){
		    cout << "The password you input is larger than the limit!" << endl;
		    cout << "1.Continue" << endl; //Back to Operation menu
		    cout << "2.Quit" << endl; //Terminate the program
		    cin >> cmd_choose;
		    if (cmd_choose == 1){break;}
		    if (cmd_choose == 2){exit(0);} //end the programme directly
		    system("pause");
		    }
	    }

	    // if the number of input account is in range
	    int i = 0;
	    for(i=0 ;i < str_test.length();i++){ //transfor str1_test to str1
             str[i] = str_test[i];
	    }
	    str[i] = '\0';
}

////////////////////////
// ↓For manager

// manager's login

manager::manager() {
	strcpy(name, "Li");
	strcpy(number, "1000");
	strcpy(password, "123456");
	person_rate = 0.05;
	enterprise_rate = 0.03;
}
char* manager::get_number() {
	return number;
}
char* manager::get_name() {
	return name;
}
char* manager::get_passsword() {
	return password;
}

//////////////////////////////////
// Interface for manager

void manager::cmd_manager() {
	int cmd_manager;
	while (1) {
		system("cls");
		cout << "Manager: " << name << endl;
		cout << "1.Create a new account" << endl;
		cout << "2.Check borrowable amount of bank" << endl;
		cout << "3.Check total_deposits of bank" << endl;
		cout << "4.Check customer's information" << endl;
		cout << "5.Reset password for customer" << endl;
		cout << "6.Quit" << endl;     // Should be 6 in requirement
		cout << "输入您的选项:" << endl;
		cin >> cmd_manager;
		if (cmd_manager == 1)this->create_account();
		if (cmd_manager == 2)this->check_borrowable();
		if (cmd_manager == 3)this->check_deposits();
		if (cmd_manager == 4)this->check_customer();
		if (cmd_manager == 5)this->Reset_password();
		//if (cmd_manager == 6)this->print();
		if (cmd_manager == 6)exit(0); //Terminate the program
		if (cmd_manager < 1 || cmd_manager > 7){cout << "Input out of range!"<< endl;}this->back_manager();
		//↑ the input number incorrect
		tsave(); 
		ttsave();
		system("pause");
		back_manager(); //After each operation, can choose leave or not
	}
}

// Create an account
// when cmd_manager == 1
void manager::create_account() {
	account* vec = new account();
	vecs.push_back(vec);
	tsave(); 
}

// Check borrowable rate        
// when cmd_manager == 2
void manager::check_borrowable() {
	borrowable_amount = 500000.0;
	for (int i = 0; i < vecs.size(); i++) {
		borrowable_amount -= vecs[i]->get_loan_amount();
		//cout << vecs[i]->get_loan_amount() << endl;
	}
	cout << "the borrowable amount:" << borrowable_amount << endl;
}

// Check the number of deposits   
// when cmd_manager == 3
void manager::check_deposits() {
	total_deposits = 200000;
	for (int i = 0; i < vecs.size(); i++) {
		total_deposits += vecs[i]->get_balance();
	}
	cout << "total deposits of bank:" << total_deposits << endl;
}

// Check customer information     
// when cmd_manager == 4
void manager::check_customer() {
	cout << "please input the account number:";
	char temp[20];
	cin >> temp;
	for (int i = 0; i < vecs.size(); i++) {
		if (strcmp(vecs[i]->get_number(), temp) == 0) {
			vecs[i]->display();
			break;
		}
	}
}

// Reset customers'password     
// when cmd_manager == 5
void manager::Reset_password() {
	cout << "please input the account number:";
	char temp[20];
	string temp_test;
	char temp_again[20];
	string temp_again_test;
	cin >> temp_test;
	password_check(temp_test, 20, temp);
	for (int i = 0; i < vecs.size(); i++) {
		if (strcmp(vecs[i]->get_number(), temp) == 0) {
			cout << "please input the new password:";
			cin >> temp;
			password_check(temp_test, 20, temp);
			cout << "please input the new password again:";
			cin >> temp_again;
			password_check(temp_again_test, 20, temp_again);
			if (strcmp(temp, temp_again) == 0) {
				vecs[i]->set_password(temp);
				cout << "Update password successfully" << endl;
			}
		}
	}
}

// Print information   
// when cmd_manager == 6
void manager::print() {
	for (int i = 0; i < vecs.size(); i++) {
		vecs[i]->display();
	}
}

// save information in the txt
void manager::ttsave() { //要改的
	borrowable_amount = 1000000.0;
	for (int i = 0; i < vecs.size(); i++) {
		borrowable_amount -= vecs[i]->get_loan_amount();
		//cout << vecs[i]->get_loan_amount() << endl;
	}
	total_deposits = 200000;
	for (int i = 0; i < vecs.size(); i++) {
		total_deposits += vecs[i]->get_balance();
	}

	FILE* fp = fopen("bank.txt", "wb");
	fprintf(fp, "%s %s %s %f %f %f %f\n", get_number(), get_name(), get_passsword(), get_barrowable(),get_total_deposits(), get_total_interstperson(), get_loan_interest());
	fclose(fp);
}

// To choose leave or not
void manager::back_manager(){
	int cmd = 0;
	while(1){
		cout << "You want to back to the menu or quit?" << endl;
		cout << "1.Continue" << endl; //Back to Operation menu
		cout << "2.Quit" << endl; //Terminate the program
		cin >> cmd;
		if (cmd == 1){cmd_manager();}
		if (cmd == 2){exit(0);} //end the programme directly
		if (cmd != 1 && cmd != 2){cout << "Input out of range!"<< endl;}this->back_manager();
		//↑ the input number incorrect
		system("pause");
		}
}

//float borrowable,
//float totaldeposits,
//float person_rate,
//float enterprise_rate
float manager::get_barrowable() {
	return borrowable_amount;
}
float manager::get_total_deposits() {
	return total_deposits;
}
float manager::get_total_interstperson() {
	return person_rate;
}
float manager::get_loan_interest() {
	return enterprise_rate;
}