#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

class Player {
private:
	double bank_balance;
	std::vector<int> hand;

public:
	Player(double x);
	void updateBalance(bool y, double amount);
	double getBalance();
	void addHand(int a);
	std::vector<int> getHand();     //polymorphism implementation 
	void clearHand();
};

#endif

