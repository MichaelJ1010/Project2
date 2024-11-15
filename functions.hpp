#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "./Cards.hpp"
#include "./User.hpp"

namespace project2 {
	void makeUser();
	void newDeck(std::vector<card::Card>& deck);
	card::Card drawCard(card::Deck& deck);
	void playerTurn(person::User player, card::Deck& deck);
}
#endif