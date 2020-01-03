#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "food.h"
#include <vector>

using namespace std;

void login();
bool validateLogin(string username, string password);
int total = 0;
int subTotal = 0;

extern "C" {
	//EXTERNAL ASM PROCEDURES
	void calcSubTotal();
	void calcTotal();
	//LOCAL C++ FNS
	int retrievePrice();
	int getQuantity();
	int addToTotal(int sub);
	void grandTotal(int total);
};

int main() {
	char c;

	do {
		calcTotal(); //asm procedure

		cout << "Do you want to add more items? (Y/N): ";
		cin >> c;
		c = toupper(c);
		//system("CLS");
	} while (c != 'N');

	if (c == 'N') {
		system("CLS");
		cout << "Total: RM" << total << endl;
	}

	return 0;
}

int addToTotal(int aSubTotal) {
	subTotal = aSubTotal;
	cout << left << setw(13) << "\n\t\tSub-Total: " << "RM " << subTotal << endl;
	return subTotal;
}

void grandTotal(int aTotal) {
	total = aTotal;
	cout << left << setw(13) << "\t\tTotal: " << "RM " << total << endl;
}

int retrievePrice() {
	int i = 0;
	int choice = 0;
	int price = 0;
	int quantity = 0;

	vector<food> items;
	items.push_back(food("Nasi Lemak", 2));
	items.push_back(food("Nasi Goreng Ayam", 7));
	items.push_back(food("Nasi Goreng Kampung", 5));
	items.push_back(food("Roti Canai", 1));
	items.push_back(food("Milo Ais", 2));
	items.push_back(food("Teh O Ais", 2));
	items.push_back(food("Kopi O Ais", 2));
	items.push_back(food("Ais Kosong", 1));

	cout << "Menu" << endl;
	cout << "=============================" << endl;

	for (vector<food>::iterator itr = items.begin(); itr != items.end(); ++itr) {
		cout << i << ". " << left << setw(16) << itr->getName() << "\t" << "RM " << itr->getPrice() << endl;
		i++;
	}

	cout << "=============================" << endl;

	cout << "Your choice: ";
	cin >> choice;

	price = items.at(choice).getPrice();

	return price;

	//TODO retrieve price and ask user for quantity, pass these two parameters to asm to calculate sub total of one item
	//TODO make asm to return these values and temporarily store in variables in c++ to pass them into another asm function to calculate sub total
}

int getQuantity() {
	int quantity;

	cout << "Quantity: ";
	cin >> quantity;

	return quantity;
}

void login() {
	string username, password;
	cout << "Enter your username: ";
	getline(cin, username);

	cout << "Enter your password: ";
	getline(cin, password);

	if (validateLogin(username, password) == true) {
		cout << "Login Successful!" << endl;
		system("pause");
		system("CLS");
		retrievePrice();
	}
	else {
		cout << "Wrong user or login password! Login unsuccessful!" << endl;
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