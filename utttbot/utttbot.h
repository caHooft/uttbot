// utttbot.h

#ifndef UTTTBOT_H
#define UTTTBOT_H

#include <string>
#include <vector>
#include "uttt.h"

class UTTTBot 
{
	int timebank;
	int time_per_move;
	std::string player_names[2];
	std::string your_bot;
	int your_botid;

	int round;
	State state;

	std::vector<std::string> split(const std::string &s, char delim);
	void setting(std::string &key, std::string &value);
	void update(std::string &key, std::string &value);
	void move(int timeout);

public:
	void run();
};

#endif // UTTTBOT_H

