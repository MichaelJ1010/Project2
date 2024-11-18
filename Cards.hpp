#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>

namespace card {
	struct Card { //struct for storing a card type and number
		short cardNumber;
		char cardType;
	};

	struct Deck { //struct for a dynamic array of cards
		std::vector<Card> deck;
	};
}
#endif // !CARDS_H
