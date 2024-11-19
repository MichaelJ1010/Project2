#include <iostream>
#include <limits>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>

#include "./User.hpp"
#include "./Cards.hpp"
#include "functions.hpp"
#include "./Choice.hpp"

using namespace std;
using namespace card;
using namespace person;
using namespace choice;


namespace project2{
	User* makeUser() {
		fstream file;
		int choice;
		string readLine;
		string username;
		string checkUsername = "null";
		string checkPassword = "null";
		short wins;
		short losses;
		string password;

		while (true) {
			cout << "Have you created an account already? (enter the number of your response) \n1.yes \n2.no" << endl;
			cin >> choice;
			switch (choice) {

			case 1:

				cout << "Username: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, username);

				cout << "\nPassword: ";
				getline(cin, password);

				file.open("data.txt");
				if (file.is_open()) {
					while (!file.eof()) {
						if (checkUsername.empty() || checkPassword.empty()) { // for the last check when there’s nothing left (VITAL)
							continue;
						}
						getline(file, readLine);
						istringstream stream(readLine);

						stream >> checkUsername >> checkPassword >> wins >> losses;
					
						if ((User{ checkUsername, checkPassword, {wins,losses} }) == (User{ username, password, {0,0} })) {
							file.close();
							return new User{ checkUsername, checkPassword, {wins,losses} };
						}	
					}
					file.close(); //ensure that you close the file, or else nothing else can access it
					cout << "Account not found." << endl;
					break;	 
				}
				file.close();

			case 2:
				cout << "Username: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, username);

				cout << "\nPassword: ";
				getline(cin, password);

				file.open("data.txt", ios::app);
				if (file.is_open()) {
					file << "\n" << username << " ";
					file << password << " ";
					file << "0 ";
					file << "0";
					file.close();
					return new User{ username, password, {0,0} };
				}				
				break;
					
			default:
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << "error, please type in 1 or 2." << endl;
				break;
			}	
		}
	}

	void newDeck(vector<Card>& deck) {
		cout << "shuffling deck..." << endl;	
		vector<Card> newDeck;
		for (short i = 3; i <= 6; i++) {
			for (short j = 1; j <= 13; j++) {
				newDeck.push_back(Card{ j, (char)i });
			}
		}
		deck = newDeck;
	}

	Card drawCard(Deck& currentDeck){
		srand(time(0));
		int randomNumber = rand() % currentDeck.deck.size();
		Card card = currentDeck.deck[randomNumber];
		cout << "Drew " << cardName(card) << card.cardType << endl;
		currentDeck.deck.erase(currentDeck.deck.begin() + randomNumber);
		if (currentDeck.deck.empty()) {
			newDeck(currentDeck.deck);
		}
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

	void menu(User* user, shared_ptr<Deck> currentDeck) {
		cout << "Welcome " << user->userName << endl;
		
		bool playing = true;
		vector<vector<short>> currentRecord = { {user->currentRecord.totalWins}, {user->currentRecord.totalLosses} };

		while (playing) {
			cout << "\n1.Play Blackjack \n2.Shuffle deck \n3.Quit" << endl;
			int choice;
			cin >> choice;
			switch (choice) {
				
				case static_cast<int>(Choice::play):
					short playerScore;
					short houseScore;
					playerScore = playerTurn(*user, *currentDeck);
					if (playerScore == 21) {
						cout << "Player wins!" << endl;
						currentRecord[0][0] = currentRecord[0][0] + 1;
						
					}
					else if (playerScore > 21) {
						cout << "Player busts! Automatic loss." << endl;
						currentRecord[1][0] = currentRecord[1][0] + 1;
					}
					else {
						houseScore = houseTurn(playerScore, *currentDeck);
						if (houseScore > 21) {
							cout << "House busts! Player wins!" << endl;
							currentRecord[0][0] = currentRecord[0][0] + 1;
						
						}
						else if (houseScore > playerScore) {
							cout << "House wins!" << endl;
							currentRecord[1][0] = currentRecord[1][0] + 1;
							
						}
						else if (houseScore == playerScore) {
							cout << "It's a tie!" << endl;
						}
						else {
							cout << "Player wins!" << endl;
							currentRecord[0][0] = currentRecord[0][0] + 1;
						}
						cout << "House score was: " << houseScore << endl;
						cout << "Player score was: " << playerScore << endl;
					}
					break;
				
				case static_cast<int>(Choice::shuffleDeck): 
					newDeck(currentDeck->deck);
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

		cout << "Would you like to save your progress? (y/n)" << endl;
		
		
		const char yes[2] = { 'y', '\0' };
		const char no[2] = { 'n', '\0' };

		
		while (true) {
		char answer[2];
		cin >> answer;
			if (strcmp(answer, yes) == 0) {
				saveProgress(*user, currentRecord);
				return;
			}
			else if (strcmp(answer, no) == 0) {
				return;

			}
			else {
				cout << "Error, try again." << endl;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				
			}
		}

	}

	bool operator==(person::User account1, person::User account2) {
		return ((account1.userName == account2.userName) && (account1.password == account2.password));
	}

	void saveProgress(const User& user, vector<vector<short>> record) {
		fstream file;
		file.open("data.txt");
		bool found = false;
		stringstream update;
		if (file.is_open()) {
			
			string readLine;
			string checkUsername, checkPassword;
			short wins, losses;
					
			while (getline(file, readLine)) {
				istringstream stream(readLine);
				stream >> checkUsername >> checkPassword >> wins >> losses;

				if (User{checkUsername, checkPassword, {wins,losses}} == user) {
			
					update << user.userName << " " << user.password << " "
						<< record[0][0] << " " << record[1][0] << "\n";
					found = true;
				}
				else {
					update << readLine << "\n";
				}
			}

			file.close();
		}

		if (found) {
			ofstream outFile("data.txt", ios::out | ios::trunc);

			outFile << update.str();
			outFile.close();
			cout << "Progress saved successfully!" << endl;
		}
		else {
			cout << "User not found. No changes made." << endl;
		}
	}

}

