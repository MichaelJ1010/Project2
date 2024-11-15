#ifndef USER_H
#define USER_H

#include <string>

namespace person{

	struct Record {
		short totalWins;
		short totalLosses;
	};

	struct User {
		std::string userName;
		std::string password;
		Record currentRecord;
	};

}
#endif