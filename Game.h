#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Dealer.h"
#include "Player.h"
//#include "Deck.h"
#include <stack>
#include <queue>

using namespace std;

class Game {
private:
	int amount;
	int betAmount;
	int handnumber;


public:
    Game();
    int start();
	void shuffle(int cards[], int SIZE, queue<int>& CARDS);
	void checkWinner(int& dealerTotal, int& playerTotal, Player& player, double bet, int attempt, stringstream& curr);
	void displayCards(int number);
    void displayDice(int number);
   virtual std::vector<int> getHand();      //polmorphism implemantation 
};

#endif 
