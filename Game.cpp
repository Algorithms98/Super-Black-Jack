#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Player.h"
#include "Dealer.h"
#include "Game.h"
using namespace std;

//ifstream input("myfile.txt");           //opening the bank file 

enum CARD {
	A = 11, J = 10, K = 10, Q = 10
};


int Game::start() {
    
    stack<string> history;
    
	const int SIZE = 52;
	int cards[SIZE] = {
	A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, K, Q,
	A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, K, Q,
	A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, K, Q,
	A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, K, Q,
	};
	
	double money;
	ifstream input("myfile.txt");
	input >> money;
	input.close();
	Player Player1(money);
	Dealer House1(1000);
	double bet;
	int attempt = 1;
	char reply;
	queue<int> CARDS;
	stringstream curr;
	string current;
	
	do {
		stringstream curr;
		cout << "Welcome to Super Blackjack" << endl << endl;
		cout << "Loading bank balance..." << endl << endl;
		cout << "----------- HAND 1 -----------" << endl;
		cout << "You have " << Player1.getBalance() << " dollars." << endl << endl;
		cout << "How many dollars do you want to bet? " << endl;
		cin >> bet;
		cout << endl << "Dealing Cards" << endl;
		
		shuffle(cards, SIZE, CARDS);
		
		int dealerTotal = 0;
		int playerTotal = 0;
		
		//Dealing cards for the first round from the queue
		for (int i = 0; i < 2; i++) {
		    
			Player1.addHand(CARDS.front());
			playerTotal += CARDS.front();
			CARDS.pop();
			
			House1.addHand(CARDS.front());
			dealerTotal += CARDS.front();
			CARDS.pop();
		}
		
		//If the dealer's hand is less than 17 add more cards 
		while (dealerTotal < 17) {
			House1.addHand(CARDS.front());
			dealerTotal += CARDS.front();
			CARDS.pop();
		}
		vector<int> dealer = House1.getHand();
		vector<int> player = Player1.getHand();

		
		cout << "Dealer shows" << endl << endl;
		displayCards(dealer[0]);
		
		cout << endl << endl;
		cout << "Player hand" << endl << endl;
		
		//Displaying the players cards 
		for (int i = 0; i < player.size(); i++) {
			displayCards(player[i]);
			cout << endl << endl;
		}
		cout << "Your hand value:  " << playerTotal << endl;
		if (playerTotal == 21) {
			cout << "You hit blackjack on the deal..." << endl;
			cout << "You won " << bet << " dollars" << endl;
			Player1.updateBalance(true, bet);
			curr << "Hand: " << attempt << " Player: " << playerTotal << "          Dealer: " << dealerTotal << "Result: Player Won. Blackjack on deal." << endl;
			break;
		}
		cout << "Enter 's' to stay, 'h' to hit on a card, or 'd' to hit on a dice: " << flush;
		cin >> reply;
		
		while (reply == 's' || reply == 'h' || reply == 'd') {

			switch (reply) {
			case 's':
				cout << "You chose to stay." << endl << endl;
				cout << "Dealer hand" << endl << endl;
				for (int i = 0; i < dealer.size(); i++) {
					displayCards(dealer[i]);
					cout << endl << endl;
				}
				cout << "Dealer hand value: " << dealerTotal << endl;
				checkWinner(dealerTotal, playerTotal, Player1, bet, attempt, curr);
				reply = 'z';
				break;
				
			case 'h':
				cout << "You chose to hit on a card." << endl << endl;
				cout << "New card: " << endl;
				Player1.addHand(CARDS.front());
				playerTotal += CARDS.front();
				displayCards(CARDS.front());
				cout << endl << endl;
				cout << "Your hand value " << playerTotal << endl;
				CARDS.pop();
				cout << "Enter 's' to stay, 'h' to hit on a card, or 'd' to hit on a dice: " << flush;
				cin >> reply;
				break;
				
			case 'd':
				cout << "You chose to hit with a dice." << endl;
				cout << "New dice: " << endl << endl;
				int dice = rand() % 6 + 1;
				Player1.addHand(dice);
				playerTotal += dice;
				displayDice(dice);
				cout << endl << endl;
				cout << "Your hand value " << playerTotal << endl;
				cout << "Enter 's' to stay, 'h' to hit on a card, or 'd' to hit on a dice: " << flush;
				cin >> reply;
				break;
			}
		}
		
		Player1.clearHand();
		House1.clearHand();
		
		cout << "Enter 'c' to continue playing or 'q' to quit: " << flush;
		cin >> reply;
		current = curr.str();
		history.push(current);
		attempt++;
        
	} while (reply == 'c');
	cout << endl << endl;
	
	//Reporting the game history 
	while (!history.empty()) {
		cout << history.top() << endl;
		history.pop();
	}
	
	//Closing the bank file 
	input.close();
	ofstream inputs("myfile.txt");
	//Writing the new balance to the file 
	inputs << endl;
    inputs << "New balance: " << Player1.getBalance();
    
	return 0;
}


//Shuffling the cards 
void Game::shuffle(int cards[], int SIZE, queue<int>& CARDS) {
    srand (time(NULL));
	int pos1, pos2;
	for (int i = 0; i < SIZE; i++) {
		pos1 = rand() % 26;
		pos2 = rand() % 26 + rand() % 26;
		swap(cards[pos1], cards[pos2]);
	}
	for (int i = 0; i < SIZE; i++) {
		CARDS.push(cards[i]);
	}
}


//Getting the player's hand 
vector<int> Game::getHand() {
    std::vector<int> v;
    return  v;
}

void Game::checkWinner(int& dealerTotal, int& playerTotal, Player& player, double bet, int attempt, stringstream& curr) {
	if (dealerTotal > playerTotal && dealerTotal <= 21) {
		cout << "You had " << playerTotal << " and the dealer had " << dealerTotal << "." << endl;
		cout << "You lost " << bet << " dollars." << endl;
		player.updateBalance(false, bet);
	
		curr << "Hand: " << attempt << " Player: " << playerTotal << "          Dealer: " << dealerTotal << "     Result: Player Lost. Score below dealer." << endl;
	}
	else if (dealerTotal < playerTotal && playerTotal <= 21) {
		cout << "You had " << playerTotal << " and the dealer had " << dealerTotal << "." << endl;
		cout << "You won " << bet << " dollars." << endl;
		player.updateBalance(true, bet);
	
		curr << "Hand: " << attempt << " Player: " << playerTotal << "          Dealer: " << dealerTotal << "     Result: Player Won. Score above dealer." << endl;
	}
	else if(dealerTotal  == playerTotal) {
		cout << "You had " << playerTotal << " and the dealer had " << dealerTotal << "." << endl;
		cout << "You won " << 0 << " dollars." << endl;
	
		curr << "Hand: " << attempt << " Player: " << playerTotal << "          Dealer: " << dealerTotal << "     Result: Draw." << endl;
	}
	else if(dealerTotal > 21 && playerTotal < 21){
		cout << "You had " << playerTotal << " and the dealer had " << dealerTotal << "." << endl;
		cout << "Dealer busts. You won " << bet << " dollars." << endl;
		player.updateBalance(true, bet);

		curr << "Hand: " << attempt << " Player: " << playerTotal << "          Dealer: " << dealerTotal << "     Result: Player Won. Dealer bust." << endl;
	}
	else if (dealerTotal < 21 && playerTotal > 21) {
		cout << "You had " << playerTotal << " and the dealer had " << dealerTotal << "." << endl;
		cout << "You bust. You lost " << bet << " dollars." << endl;
		player.updateBalance(false, bet);

		curr << "Hand: " << attempt << " Player: " << playerTotal << "          Dealer: " << dealerTotal << "     Result: Player Lost. Player bust." << endl;
	}
}


//Displaying the cards 
void Game::displayCards(int number) {

	switch (number) {

	case 2:
		cout << "+ -----------------------+" << endl;
		cout << "| 2                      |" << endl;
		cout << "|                        |" << endl;
		cout << "|          **  **        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|           ****         |" << endl;
		cout << "|            **          |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "+------------------------+" << endl;
		break;

	case 10:
		cout << "+ -----------------------+" << endl;
		cout << "|  10                    |" << endl;
		cout << "|                        |" << endl;
		cout << "|          **            |" << endl;
		cout << "|        ******          |" << endl;
		cout << "|        ******          |" << endl;
		cout << "|          **            |" << endl;
		cout << "|        ******          |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "+------------------------+	" << endl;
		break;

	case 11:
		cout << "+ -----------------------+" << endl;
		cout << "|  A                     |" << endl;
		cout << "|                        |" << endl;
		cout << "|        ** ** **        |" << endl;
		cout << "|         ******         |" << endl;
		cout << "|          ****          |" << endl;
		cout << "|           **           |" << endl;
		cout << "|          ****          |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "+------------------------+	" << endl;
		break;

	case 8:
		cout << "+ -----------------------+" << endl;
		cout << "| J                      |" << endl;
		cout << "|                        |" << endl;
		cout << "|          **  **        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|           ****         |" << endl;
		cout << "|            **          |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "+------------------------+	" << endl;
		break;

	case 4:
		cout << "+ -----------------------+" << endl;
		cout << "|  4                     |" << endl;
		cout << "|                        |" << endl;
		cout << "|        ** ** **        |" << endl;
		cout << "|         ******         |" << endl;
		cout << "|          ****          |" << endl;
		cout << "|           **	          |" << endl;
		cout << "|          ****          |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "+------------------------+	" << endl;
		break;

	case 5:
		cout << "+ -----------------------+" << endl;
		cout << "|  5                     |" << endl;
		cout << "|                        |" << endl;
		cout << "|          **  **        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|           ****         |" << endl;
		cout << "|            **          |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "+------------------------+	" << endl;
		break;

// 	case 10:
// 		cout << "+ -----------------------+" << endl;
// 		cout << "|	Q					  |" << endl;
// 		cout << "|						  |" << endl;
// 		cout << "|	   		**  ** 		  |" << endl;
// 		cout << "|	   		******		  |" << endl;
// 		cout << "|	   		******		  |" << endl;
// 		cout << "|			 ****		  |" << endl;
// 		cout << "|		  	  **		  |" << endl;
// 		cout << "|						  |" << endl;
// 		cout << "|						  |" << endl;
// 		cout << "|						  |" << endl;
// 		cout << "|						  |" << endl;
// 		cout << "+------------------------+	" << endl;
// 		break;


	case 3:
		cout << "+ -----------------------+" << endl;
		cout << "|  3                     |" << endl;
		cout << "|                        |" << endl;
		cout << "|            **          |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|           ****         |" << endl;
		cout << "|            **          |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "+------------------------+" << endl;
		break;

	case 9:
		cout << "+ -----------------------+" << endl;
		cout << "|  9                     |" << endl;
		cout << "|                        |" << endl;
		cout << "|            **          |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|           ****         |" << endl;
		cout << "|            **          |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "+------------------------+	" << endl;
		break;

	case 7:
		cout << "+ -----------------------+" << endl;
		cout << "|  7                     |" << endl;
		cout << "|                        |" << endl;
		cout << "|          **  **        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|           ****         |" << endl;
		cout << "|            **          |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "+------------------------+	" << endl;
		break;

	case 6:
		cout << "+ -----------------------+" << endl;
		cout << "|  6                     |" << endl;
		cout << "|                        |" << endl;
		cout << "|            **          |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|          ******        |" << endl;
		cout << "|           ****         |" << endl;
		cout << "|            **          |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "|                        |" << endl;
		cout << "+------------------------+	" << endl;
		break;

	}
}

//Displaying the dice 
void Game::displayDice(int number) {
	switch (number) {
	case 1:
		cout << "+---------------+" << endl;
		cout << "|               |" << endl;
		cout << "|               |" << endl;
		cout << "|       *       |" << endl;
		cout << "|               |" << endl;
		cout << "|               |" << endl;
		cout << "+---------------+" << endl;
		break;
	case 2:
		cout << "+---------------+" << endl;
		cout << "|  *            |" << endl;
		cout << "|               |" << endl;
		cout << "|               |" << endl;
		cout << "|               |" << endl;
		cout << "|            *  |" << endl;
		cout << "+---------------+" << endl;
		break;
	case 3:
		cout << "+---------------+" << endl;
		cout << "|       *       |" << endl;
		cout << "|               |" << endl;
		cout << "|               |" << endl;
		cout << "|               |" << endl;
		cout << "|  *         *  |" << endl;
		cout << "+---------------+" << endl;
		break;
	case 4:
		cout << "+---------------+" << endl;
		cout << "|  *         *  |" << endl;
		cout << "|               |" << endl;
		cout << "|               |" << endl;
		cout << "|               |" << endl;
		cout << "|  *         *  |" << endl;
		cout << "+---------------+" << endl;
		break;
	case 5:
		cout << "+---------------+" << endl;
		cout << "|  *         *  |" << endl;
		cout << "|               |" << endl;
		cout << "|       *       |" << endl;
		cout << "|               |" << endl;
		cout << "|  *         *  |" << endl;
		cout << "+---------------+" << endl;
		break;
	case 6:
		cout << "+---------------+" << endl;
		cout << "|  *         *  |" << endl;
		cout << "|               |" << endl;
		cout << "|  *         *  |" << endl;
		cout << "|               |" << endl;
		cout << "|  *         *  |" << endl;
		cout << "+---------------+" << endl;
		break;
	}
}
