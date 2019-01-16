// utttbot.cpp

#include "utttbot.h"
#include <iostream>
#include <sstream>
using namespace std;

array<int, 9> scores = { 0,0,0,0,0,0,0,0,0 };

void UTTTBot::run() 
{
	std::string line;
	while (std::getline(std::cin, line)) 
	{
		std::vector<std::string> command = split(line, ' ');
		if (command[0] == "settings") 
		{
			setting(command[1], command[2]);
		} 
		
		else if (command[0] == "update" && command[1] == "game") 
		{
			update(command[2], command[3]);
		} 
		
		else if (command[0] == "action" && command[1] == "move") 
		{
			move(std::stoi(command[2]));
		} 
		
		else 
		{
			std::cerr << "Unknown command: " << line << std::endl;
		}
	}
}

void UTTTBot::mcUpdateScores(array<int, 9> &subscores, State &trialboard, Player &winner)
{
	for (int i = 0; i < 9; i++)
	{
		if (winner == Player::X)
		{
			if (trialboard[i] == Player::X)
			{
				subscores[i]++;
			}

			if (trialboard[i] == Player::O)
			{
				subscores[i]--;
			}
		}

		if (winner == Player::O)
		{
			if (trialboard[i] == Player::X)
			{
				subscores[i]--;
			}

			if (trialboard[i] == Player::O)
			{
				subscores[i]++;
			}
		}
	}


	for (int i = 0; i < 9; i++)
	{
		scores[i] = scores[i] + subscores[i];
	}
}

State UTTTBot::mcTrial(const State &board)
{
	State trialboard = board;
	array<int, 9> subscores = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	Player winner;

	vector<Move> moves = getMoves(trialboard);

	while (moves.size() != 0)
	{
		trialboard = doMove(trialboard, moves[(rand() % moves.size())]);
		moves = getMoves(trialboard);
	}

	winner = getWinner(trialboard);

	mcUpdateScores(subscores, trialboard, winner);


	return board;
}

Move UTTTBot::getBestMove(State &board)
{
	int highest = -9999;
	int index = -1;

	for (int i = 0; i < 9; i++)
	{
		if (scores[i] > highest && board[i] == Player::None)
		{
			highest = scores[i];
			index = i;
		}
	}

	return index;
}

Move UTTTBot::mcMove(State &board, const Player &player)
{
	scores = { 0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < 20; i++)
	{
		board = mcTrial(board);
	}

	return getBestMove(board);
}


void UTTTBot::move(int timeout) 
{
	// Do something more intelligent here than return a random move
	//std::vector<Move> moves = getMoves(state);

	//std::cout << "place_disc " << mcMove(board), getCurrentPlayer(board) << std::endl;
	//cout << "place_disc " << board= doMove(board, mcMove(board, getCurrentPlayer(board))), getCurrentPlayer(board) << std::endl;
	
}

void UTTTBot::update(std::string &key, std::string &value)
{
	if (key == "round") 
	{
		round = std::stoi(value);
	} else if (key == "field") 
	{
		int row = 0;
		int col = 0;
		std::vector<std::string> fields = split(value, ',');
		for (std::string &field : fields) 
		{
			if (field == "0") 
			{
				state.board[row][col] = Player::X; 
			} 
			
			else if (field == "1") 
			{
				state.board[row][col] = Player::O;
			} 
			
			else 
			{
				state.board[row][col] = Player::None;
			}
			col++;
			
			if (col == 9) 
			{
				row++; 
				col = 0;
			}
		}
	} else if (key == "macroboard") 
	{
		int row = 0;
		int col = 0;
		std::vector<std::string> fields = split(value, ',');
		for (std::string &field : fields) 
		{
			if (field == "-1") 
			{
				state.macroboard[row][col] = Player::Active;
			} 
			
			else if (field == "0") 
			{
				state.macroboard[row][col] = Player::X;
			} 
			
			else if (field == "1") 
			{
				state.macroboard[row][col] = Player::O;
			} 
			
			else 
			{
				state.macroboard[row][col] = Player::None;
			}

			col++;

			if (col == 3) 
			{
				row++;
				col = 0;
			}
		}
	}
}

void UTTTBot::setting(std::string &key, std::string &value) {
	if (key == "timebank") 
	{
		timebank = std::stoi(value);
	} 
	
	else if (key == "time_per_move") 
	{
		time_per_move = std::stoi(value);
	} 
	
	else if (key == "player_names") 
	{
		std::vector<std::string> names = split(value, ',');
		player_names[0] = names[0];
		player_names[1] = names[1];
	} 
	
	else if (key == "your_bot") 
	{
		your_bot = value;
	} 
	
	else if (key == "your_botid") 
	{
		your_botid = std::stoi(value);
	}
}

std::vector<std::string> UTTTBot::split(const std::string &s, char delim) 
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;

	while (std::getline(ss, item, delim)) 
	{
		elems.push_back(item);
	}
	return elems;
}

