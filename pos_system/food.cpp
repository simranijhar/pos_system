#include "food.h"

food::food() {
	newPrice = 0;
}

food::food(string name, double price) {
	newName = name;
	newPrice = price;
}

food::~food() {
}

string food::getName() const {
	return newName;
}

double food::getPrice() const {
	return newPrice;
}

void food::setName(string name) {
	newName = name;
}

void food::setPrice(double price) {
	newPrice = price;
}