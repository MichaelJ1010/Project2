#ifndef USER_H
#define USER_H

#include <string>

namespace person{

	struct Record { //struct that maintains a record of wins and losses
		short totalWins;
		short totalLosses;
	};

	struct User { //struct for keeping track of a user	
		std::string userName;
		std::string password;
		Record currentRecord;
	};

}
#endif