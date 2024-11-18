#include <iostream>
#include <memory>
#include "./User.hpp"
#include "./Cards.hpp"
#include "./functions.hpp"

using namespace std;
using namespace card;
using namespace person;
using namespace project2;

int main() {
	
	User* user = makeUser();
	vector<Card> deck;
	newDeck(deck);
	Deck newDeck{ deck };
	shared_ptr<Deck> currentDeck = make_shared<Deck>(newDeck);
	menu(user, currentDeck);

	delete user;
	user = nullptr;
	return 0;
}