#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "food.h"
#include <vector>

using namespace std;

//TODO retrieve price and ask user for quantity, pass these two parameters to asm to calculate sub total of one item
//TODO make asm to return these values and temporarily store in variables in c++ to pass them into another asm function to calculate sub total

//function declaration
bool validateLogin(string username, string password);
void calcSplitBill();
void login();
void displayMenu();
void makeOrder(vector<food> items);

//global variables
int total = 0;
int subTotal = 0;

extern "C" {
	//EXTERNAL ASM PROCEDURES
	int calcSubTotal(int price, int quantity);
	int calcTotal(int subTotal, int total);
	int calcDivision(int total, int numOfPerson);

	//LOCAL C++ FNS
};

int main() {
	//calcSplitBill();

	login();

	return 0;
}

void login() {
	string username, password;

	cout << "Enter your username: ";
	getline(cin, username);

	cout << "Enter your password: ";
	getline(cin, password);

	if (validateLogin(username, password)) {
		cout << "Login Successful" << endl;
		system("pause");
		system("CLS");
		displayMenu();
	}
	else {
		cout << "Wrong Login Information!" << endl;
		system("pause");
		system("CLS");
		login();
	}
}

void displayMenu() {
	int i = 0;

	vector<food> items;
	items.push_back(food("Nasi Lemak", 2));
	items.push_back(food("Nasi Goreng Ayam", 7));
	items.push_back(food("Nasi Goreng Kampung", 5));
	items.push_back(food("Roti Canai", 1));
	items.push_back(food("Milo Ais", 2));
	items.push_back(food("Teh O Ais", 1));
	items.push_back(food("Kopi O Ais", 2));
	items.push_back(food("Ais Kosong", 1));

	cout << "Menu" << endl;
	cout << "=============================" << endl;
	for (vector<food>::iterator itr = items.begin(); itr != items.end(); ++itr) {
		cout << i << ". " << left << setw(16) << itr->getName() << "\t" << "RM " << itr->getPrice() << endl;
		i++;
	}
	cout << "=============================" << endl;

	makeOrder(items);
}

void makeOrder(vector<food> items) {
	int choice = 0;
	int price = 0;
	int quantity = 0;
	char c;

	do {
		cout << "Your choice: ";
		cin >> choice;

		price = items.at(choice).getPrice();

		cout << "Quantity: ";
		cin >> quantity;

		subTotal = calcSubTotal(price, quantity);
		cout << right << setw(16) << "\t\tSub Total: RM" << subTotal << endl;
		total = calcTotal(subTotal, total);
		cout << right << setw(16) << "\t\tTotal: RM" << total << endl;

		cout << "Do you want to add more items? (Y/N): ";
		cin >> c;
		c = toupper(c);
	} while (c != 'N');

	if (c == 'N') {
		system("CLS");
		cout <<"Total: RM" << total << endl;
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

void calcSplitBill() {
	char i; //input
	int numOfPerson;

	cout << "Do you want to split the bill? (Y/N): ";
	cin >> i;
	i = toupper(i);

	if (i == 'Y') {
		cout << "How many people? (Eg : 2): ";
		cin >> numOfPerson;

		int split = calcDivision(total, numOfPerson);
		cout << "Each person pays: " << split;
	}

	else if (i == 'N') {
		cout << "Total: RM" << total << endl;
	}

	else {
		cout << "Please enter Y/N";
	}
}