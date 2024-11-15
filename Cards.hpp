#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>

namespace card {
	struct Card {
		short cardNumber;
		char cardType;
	};

	struct Deck {
		std::vector<Card> deck;
	};
}
#endif // !CARDS_H
