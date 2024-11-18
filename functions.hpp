#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <memory>
#include "./Cards.hpp"
#include "./User.hpp"

namespace project2 {
	person::User* makeUser(); //either creates a new user or selects a user mentioned from a data.txt file
	void newDeck(std::vector<card::Card>& deck); //creates a full deck of cards
	card::Card drawCard(card::Deck& deck); //draws a card from a deck
	short playerTurn(person::User player, card::Deck& deck); //plays a round of blackjack for the user
	std::string cardName(card::Card& card); //prints out unique card names for certain cards, like ace and face cards
	short houseTurn(short playerScore, card::Deck& currentDeck); //simulates the turn of the house
	void menu(person::User* user, std::shared_ptr<card::Deck> deck); //option screen to give user choices on what they want to do
	bool operator==(person::User account1, person::User account2); //compares two account names and passwords
	void saveProgress(person::User player); //saves the progress of the user in data.txt


}
#endif