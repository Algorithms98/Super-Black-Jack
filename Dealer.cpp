#include "Dealer.h"

Dealer::Dealer(double x) : bank_balance(x) {};
void Dealer::updateBalance(bool y, double amount) {
	if (y) bank_balance += amount;      //Rewarding the dealer with more money 
	else bank_balance -= amount;        //Take away money from the dealer 
}
void Dealer::addHand(int a) {
	hand.push_back(a);                  //
}
std::vector<int> Dealer::getHand() {
	return hand;
}
void Dealer::clearHand() {
	hand.clear();
}