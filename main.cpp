#include <iostream>
#include "./User.hpp"
#include "./Cards.hpp"
#include "./functions.hpp"

using namespace std;
using namespace card;
using namespace person;
using namespace project2;

int main() {
	short currentWins;
	short currentLosses;
	makeUser();
	vector<Card> deck;
	newDeck(deck);
	/*vector<Card> deck{ Card{'1', "Spades"}, Card{'2', "Spades"} };*/
	User newUser{ "Michael", "Johnson", {0,0} };
	Deck newDeck{ deck };


	//drawCard(newDeck);

	//for (auto card : newDeck.deck) {
	//	cout << card.cardNumber << card.cardType << endl;
	//}	
	
		playerTurn(newUser, newDeck);

	
	return 0;
}