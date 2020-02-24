#pragma once
#ifndef DEALER_H
#define DEALER_H
#include <vector>

class Dealer {
private:
	double bank_balance;
	std::vector<int> hand;

public:
	Dealer(double x);
	void updateBalance(bool y, double amount);
	void addHand(int a);
	std::vector<int> getHand();         //polymorphism implementation 
	void clearHand();
};
#endif
