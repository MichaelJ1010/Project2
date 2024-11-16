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
		cout << "Drew " << cardName(card) << card.cardType << endl;
		currentDeck.deck.erase(currentDeck.deck.begin() + randomNumber);

		return card;
	}

	short playerTurn(User player, Deck& currentDeck) {
		Card card1 = drawCard(currentDeck);
		Card card2 = drawCard(currentDeck);
		string decision;
		short cardTotal;
		cardTotal = card1.cardNumber + card2.cardNumber;
		
		
		while (true) {

		cout << "You are at " << cardTotal << " points." << endl;
		cout << "Would you like to hit or stand?" << endl;
		getline(cin, decision);

		if (decision.find("hit") != string::npos) {
			Card newCard = drawCard(currentDeck);
			cardTotal += newCard.cardNumber;
			if (cardTotal >= 21) {
				break;
			}
		}
		else if(decision.find("stand") != string::npos) {
			cout << "standing at " << cardTotal << "\n\n";

			break;
		}
		else {
			cout << "error, please try again." << endl;
			
		}
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}

		return cardTotal;
	}

	string cardName(Card& card) {
		if (card.cardNumber == 1) {
			return "A";
		}
		if (card.cardNumber == 11) {
			card.cardNumber = 10;
			return "J";
		}
		if (card.cardNumber == 12) {
			card.cardNumber = 10;
			return "Q";
		}
		if (card.cardNumber == 13) {
			card.cardNumber = 10;
			return "K";
		}
		return to_string(card.cardNumber);
	}


}

