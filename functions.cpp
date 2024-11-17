#include <iostream>
#include <limits>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>

#include "./User.hpp"
#include "./Cards.hpp"
#include "functions.hpp"
#include "./Choice.hpp"

using namespace std;
using namespace card;
using namespace person;
using namespace choice;


namespace project2{
	User makeUser() {
		cout << "Have you created an account already? (enter the number of your response) \n1.yes \n2.no" << endl;
		fstream file;

		while (true) {
			int choice;
			string username;
			string checkUsername = "null";
			string checkPassword = "null";
			string wins;
			string losses;
			string password;
			cin >> choice;
			switch (choice) {

			case 1:

				cout << "Username: ";
				cin.clear();
				cin.ignore();
				getline(cin, username);

				cout << "\nPassword: ";
				getline(cin, password);

				file.open("data.txt");
				if (file.is_open()) {
					while (!file.eof()) {
						if (checkUsername.empty()) { // for the last check when there’s nothing left (VITAL)
							continue;
						}

						getline(file, checkUsername, ',');
						file.ignore();
						getline(file, checkPassword, ',');
						file.ignore();
						getline(file, wins, ',');
						file.ignore();
						getline(file, losses, '\n');
						file.ignore();
						User checkUser{ checkUsername, checkPassword, {(short)stoi(wins),(short)stoi(losses)} };
						if (checkUser == User{ username, password, {0,0} }) {
							//return checkUser;
						}

						cout << checkUsername << endl;
						cout << username << endl;
						cout << (checkUsername == username) << endl;
						if (checkUsername == username) {
							cout << "username exists." << endl;

						}
					}
					file.close(); //ensure that you close the file, or else nothing else can access it

				}
			case 2:
				cout << "Username: ";
				cin.clear();
				cin.ignore();
				getline(cin, username);

				cout << "\nPassword: ";
				getline(cin, password);

				file.open("data.txt");
				if (file.is_open()) {
					while (!file.eof()) {
						if (checkUsername.empty()) {
							continue;
						}
						getline(file, checkUsername, '\n');
						file.ignore();

					}
				}
				file << username << ",";
				file << password << ",";
				file << "0,";
				file << "0\n";
				break;
				//file << username << ",";	
				//file << password << '\n';
				//cout << filesystem::current_path() << endl;
				file.close();


			}
		}
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
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

	short houseTurn(short playerScore, Deck& currentDeck) {

		Card card1 = drawCard(currentDeck);
		Card card2 = drawCard(currentDeck);
		
		short cardTotal;
		cardTotal = card1.cardNumber + card2.cardNumber;

		while (true) {
			if ((cardTotal > playerScore) || (cardTotal == 21)) {
				break;
			}
			Card newCard = drawCard(currentDeck);
			cardTotal += newCard.cardNumber;
		}

		return cardTotal;
	}

	void menu(User newUser, Deck& newDeck) {
		cout << "Welcome." << endl;
		
		bool playing = true;
		
		while (playing) {
			cout << "\n1.Play Blackjack \n2.Shuffle deck \n3.Quit" << endl;
			int choice;
			cin >> choice;
			switch (choice) {
				case static_cast<int>(Choice::play):
					short playerScore;
					short houseScore;
					playerScore = playerTurn(newUser, newDeck);
					if (playerScore == 21) {
						cout << "Player wins!" << endl;
					}
					else if (playerScore > 21) {
						cout << "Player busts! Automatic loss." << endl;
					}
					else {
						houseScore = houseTurn(playerScore, newDeck);
						if (houseScore > 21) {
							cout << "House busts! Player wins!" << endl;
						}
						else if (houseScore > playerScore) {
							cout << "House wins!" << endl;
						}
						else if (houseScore == playerScore) {
							cout << "It's a tie!" << endl;
						}
						else {
							cout << "Player wins!" << endl;
						}
						cout << "House score was: " << houseScore << endl;
						cout << "Player score was: " << playerScore << endl;
					}
					break;
				case static_cast<int>(Choice::shuffleDeck): 
					break;
				case static_cast<int>(Choice::quit):
					playing = false;
					break;
				default:
					cout << "Error, please try again." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
			}


		}
		

	}

	bool operator==(person::User account1, person::User account2) {
		return ((account1.userName == account2.userName) && (account1.password == account2.password));
	}

}

