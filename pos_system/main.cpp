#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "food.h"
#include <vector>
#include <windows.h>

using namespace std;

//function declaration
bool validateLogin(string username, string password);
void calcSplitBill();
void login();
void displayMenu();
void makeOrder(vector<food> items);
void resetProg();
void displayMain();

//global variables
double total = 0.0;
double subTotal = 0.0;
double grandTotal = 0.0;
double cst = 0.0;
double sst = 0.0;

extern "C" {
	//EXTERNAL ASM PROCEDURES
	void calcSubTotal(double price, double quantity); //asm procedure to calculate sub total for each item
	void calcTotal(double subTotal, double total); //asm procedure to calculate total
	void splitBill(double total, double numOfPerson);//asm procedure to split bill between people
	void calcCST(double total); //asm procedure to calculate customer service tax
	void calcSST(double total); //asm procedure to calculate sales & service tax
	void calcGrandTotal(double total, double cst, double sst);
	void calcBalance(double grandTotal, double payment);

	//LOCAL C++ FNS
	void displaySubTotal(double subTotal); //function to display sub total
	void displayTotal(double total); //function to display total
	void displaySplitAmount(double amount); //function to display split amount
	void displayCST(double total);
	void displaySST(double total);
	void displayGrandTotal(double grandTotal);
	void displayBalance(double change);
};

int main() {
	
	displayMain();
	return 0;
}

void displayMain() {
	cout << ">>> Welcome to Shaq Donald's! <<<\n" << endl;
	login();
}

void login() {
	string username, password;

	cout << "=====================" << endl;
	cout << right << setw(13) << "Login" << endl;
	cout << "=====================" << endl;

	cout << "\nEnter your username: ";
	getline(cin, username);

	//input masked
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

	//password input
	cout << "Enter your password: ";
	getline(cin, password);

	//reset console back to normal
	SetConsoleMode(hStdin, mode);

	if (validateLogin(username, password)) {
		system("CLS");
		cout << "Login Successful" << endl;
		system("pause");
		system("CLS");
		displayMenu();
	}
	else {
		cout << "\nWrong Login Information!" << endl;
		system("pause");
		system("CLS");
		login();
	}
}

bool validateLogin(string username, string password) {
	string usr, pass;

	fstream loginFile;
	loginFile.open("login.txt");

	if (!loginFile.is_open())
	{
		cout << "Unable to open file";
	}

	while (loginFile) {
		getline(loginFile, usr, ',');
		getline(loginFile, pass, '\n');

		if (usr.compare(username) == 0 && pass.compare(password) == 0) {
			return true;
		}
	}
	loginFile.close();
	return false;
}

void makeOrder(vector<food> items) {
	int choice = 0;
	double price = 0.0;
	double quantity = 0.0;
	char choice1, choice2;
	double amtPaid = 0.0;

	do {
		cout << "Your choice: ";
		cin >> choice;

		if (choice == 99) {
			system("CLS");
			cout << "Program Exiting..." << endl;
			system("pause");
			exit(0);
		}

		price = items.at(choice).getPrice();

		cout << "Quantity: ";
		cin >> quantity;

		calcSubTotal(price, quantity);
		calcTotal(subTotal, total);

		cout << "Do you want to add more items? (Y/N): ";
		cin >> choice1;
		choice1 = toupper(choice1);
	} while (choice1 != 'N');

	if (choice1 == 'N') {
		system("CLS");
		cout << "Total: RM" << total << endl;
		calcCST(total);
		calcSST(total);
		calcGrandTotal(total, cst, sst);

		cout << "Do you want to split the bill? (Y/N): ";
		cin >> choice2;
		choice2 = toupper(choice2);

		if (choice2 == 'Y') {
			calcSplitBill();
			resetProg();
		}
		else {
			do{
				cout << "Amount paid by customer: RM";
				cin >> amtPaid;
				if (amtPaid < grandTotal) {
					cout << "Not allowed! Customer should pay more or same amount!" << endl;
				}
				else {
					calcBalance(grandTotal, amtPaid);
				}				
			} while (amtPaid < grandTotal);
			cout << "\n";
			resetProg();
		}
	}
}

void resetProg() {
	cout << "\n>Moving onto next order..." << endl;
	system("pause");
	system("CLS");

	total = 0.0;
	subTotal = 0.0;
	grandTotal = 0.0;
	cst = 0.0;
	sst = 0.0;

	displayMenu();
}

void displayBalance(double change) {
	cout << "Customer's change: RM" << change;
}

void calcSplitBill() {
	double numOfPerson = 0.0;
	cout << "How many people? (Eg: 2): ";
	cin >> numOfPerson;
	splitBill(grandTotal, numOfPerson);
}

void displayMenu() {
	int i = 0;

	vector<food> items;
	items.push_back(food("Nasi Lemak", 2.5));
	items.push_back(food("Nasi Goreng Ayam", 7.2));
	items.push_back(food("Nasi Goreng Kampung", 5.1));
	items.push_back(food("Roti Canai", 1.2));
	items.push_back(food("Milo Ais", 2.2));
	items.push_back(food("Teh O Ais", 1.7));
	items.push_back(food("Kopi O Ais", 2.1));
	items.push_back(food("Ais Kosong", 0.7));

	cout << "Menu" << endl;
	cout << "==============================" << endl;
	for (vector<food>::iterator itr = items.begin(); itr != items.end(); ++itr) {
		cout << i << ". " << left << setw(16) << itr->getName() << "\t" << "RM " << itr->getPrice() << endl;
		i++;
	}
	cout << "99. Exit" << endl;
	cout << "==============================" << endl;

	makeOrder(items);
}

void displaySubTotal(double aSubTotal) {
	subTotal = aSubTotal;
	cout << right << setw(16) << "\t\tSub Total: RM" << subTotal << endl;
}

void displayTotal(double aTotal) {
	total = aTotal;
	cout << right << setw(16) << "\t\tTotal: RM" << total << endl;
}

void displaySST(double _sst) {
	sst = _sst;
	cout << "+ SST: RM" << sst << endl;
}

void displayCST(double _cst) {
	cst = _cst;
	cout << "+ CST: RM" << cst << endl;
}

void displaySplitAmount(double amount) {
	cout << "Each person pays: RM" << amount << endl;
}

void displayGrandTotal(double _grandTotal) {
	grandTotal = _grandTotal;
	cout << "Grand Total: RM" << grandTotal << endl;
}