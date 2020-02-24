#include "Player.h"

Player::Player(double x) : bank_balance(x) {};

void Player::updateBalance(bool y, double amount) {
	if (y) bank_balance += amount;      //Rewarding the player with more money 
	else bank_balance -= amount;        //Subtracting money from the player's bank balance 
}
double Player::getBalance() { return bank_balance; }

void Player::addHand(int a) {
	hand.push_back(a);
}

std::vector<int> Player::getHand() {
	return hand;
}
void Player::clearHand() {
	hand.clear();
}