#include "bank.h"

 vector<account*> vecs;
//菜单入口
 void menu_back(class manager &man);
void menu(class manager &man) {
	system("cls");
	char str1[20];    //account number
	string str1_test; //To test whether the number of input account more than 20
	char str2[20];    //account password
	string str2_test;// To test whether the number of input password more than 20
	int cmd = 0;     // the choose for cmds
	int cmd_choose = 0; //the choose for quit or not

	cout << "Please input your account number:" << endl;
	cin >> str1_test;
	
	// if the number of input account is in range
	int i = 0;
	for(i=0 ;i < str1_test.length();i++){ //transfor str1_test to str1
             str1[i] = str1_test[i];
	}
	str1[i] = '\0';

	if (strcmp(str1, man.get_number()) == 0) {  //manager login, password and account are correct
	
	    cout << "Please input you account password:" << endl;
	    cin >> str2_test;

	// if the number of input password is in range
	   int m = 0;
	   for(m=0 ;m < str2_test.length();m++){ //transfor str1_test to str1
             str2[m] = str2_test[m];
	   }
	   str2[m] = '\0';

	   if(strcmp(str2, man.get_passsword()) == 0){
	       cout << "Login Success!" << endl; //我也不知道为什么见不到这段话
		    man.cmd_manager();
	   }
	   else{
			cout << "Your password is wrong!" << endl;
			cout << "Login failed!" << endl; // go to menu_back() directly
			menu_back(man);
		}
	}

	else{
		for (int i = 0; i < vecs.size(); i++) {
			if (strcmp(str1, vecs[i]->get_number()) == 0) {
	            cout << "Please input you account password:" << endl;
	            cin >> str2_test;

	            int m = 0;
	            for(m=0 ;m < str2_test.length();m++){ //transfor str1_test to str1
                         str2[m] = str2_test[m];
	            }
	           str2[m] = '\0';
			    if (strcmp(str2, vecs[i]->get_passsword()) == 0) {
					    vecs[i]->cmd_users();
					    break;
			    }
				else{
					cout << "Password wrong!" << endl;
					menu_back(man);
				}
			}
	    }
		cout << "account wrong!" << endl;
	    menu_back(man);
	 }
}

void tload() {
	FILE* fp = fopen("account.txt", "rb+");
	int size;
	fscanf(fp, "%d", &size);
	char str[8][50];
	for (int i = 0; i < size; i++) {
		fscanf(fp, "%s %s %s %s %s %s %s %s", str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
		account* vec = new account(str[0],str[1], str[2], str[3], atof(str[4]), atof(str[5]), atof(str[6]), atof(str[7]));
		//vec->display();
		//system("pause");
		vecs.push_back(vec);
	}
	fclose(fp);
}

// If the password or account is incorrect
void menu_back(class manager &man){ 
	int cmd = 0;
	while(1){
		cout << "1.Continue" << endl; //Back to Operation menu
		cout << "2.Quit" << endl; //Terminate the program
		cin >> cmd;
		if (cmd == 1){menu(man);}
		if (cmd == 2){exit(0);} //end the programme directly
		if (cmd != 1 && cmd != 2){cout << "Input out of range!"<< endl;menu_back(man);}
		//↑ the input number incorrect
		system("pause");
		}
}

int main() {
	tload();
	manager man = manager();
	while (1) {
		menu(man);
		menu_back(man); //If the password is incorrect
		system("pause");
	}
}