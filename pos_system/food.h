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
	food(string, double);

	//destructor
	~food();

	//accessor functions
	string getName() const; //returns name of food
	double getPrice() const; //returns price of food

	//mutator functions
	void setName(string); //set name of food
	void setPrice(double); //set price of food

private:
	//member variables
	string newName;
	double newPrice;
};

#endif // !FOOD_H
