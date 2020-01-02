#pragma once
#include <iostream>
#include <string>

using namespace std;

#ifndef FOOD_H
#define FOOD_H

class food
{
public:

	//default constructor
	food();

	//overload constructor
	food(string, int);

	//destructor
	~food();

	//accessor functions
	string getName() const; //returns name of food
	int getPrice() const; //returns price of food

	//mutator functions
	void setName(string); //set name of food
	void setPrice(int); //set price of food

private:
	//member variables
	string newName;
	int newPrice;
};

#endif // !FOOD_H
