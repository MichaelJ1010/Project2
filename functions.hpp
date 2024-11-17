#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include "./Cards.hpp"
#include "./User.hpp"

namespace project2 {

	person::User makeUser();
	void newDeck(std::vector<card::Card>& deck);
	card::Card drawCard(card::Deck& deck);
	short playerTurn(person::User player, card::Deck& deck);
	std::string cardName(card::Card& card);
	short houseTurn(short playerScore, card::Deck& currentDeck);
	void menu(person::User player, card::Deck& currentDeck);
	bool operator==(person::User account1, person::User account2);

}
#endif