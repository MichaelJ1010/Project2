#include <iostream>
#include <limits>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "./User.hpp"
#include "./Cards.hpp"
#include "functions.hpp"

using namespace std;
using namespace card;
using namespace person;


namespace project2{
	void makeUser() {
		string username;
		string password;
		cout << "Username: ";
		getline(cin, username);

		cout << "\nPassword: ";
		getline(cin, password);
	}

	void newDeck(vector<Card>& deck) {
		for (short i = 3; i <= 6; i++) {
			for (short j = 1; j <= 13; j++) {
				deck.push_back(Card{ j, (char)i });
			}
			
		}
	}
	Card drawCard(Deck& currentDeck){
		srand(time(0));
		int randomNumber = rand() % currentDeck.deck.size();
		//cout << randomNumber << endl;
		//cout << "Drew " << currentDeck.deck[randomNumber].cardNumber << currentDeck.deck[randomNumber].cardType << endl;
		Card card = currentDeck.deck[randomNumber];
		
		currentDeck.deck.erase(currentDeck.deck.begin() + randomNumber);

		return card;
	}
	void playerTurn(User player, Deck& currentDeck) {
		Card card1 = drawCard(currentDeck);
		Card card2 = drawCard(currentDeck);
		cout << "Drew " << card1.cardNumber << card1.cardType << " and " << card2.cardNumber << card2.cardType << endl;
		cout << "You are at " << card1.cardNumber + card2.cardNumber << " points." << endl;
	}

}

