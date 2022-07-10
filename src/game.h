#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <iostream>

#include "utils/utils.h"

#include "board.h"
#include "player.h"

class Game {
private:
	Player white;
	Player black;
	Board m_Board;

	int turnCount{};
	bool currentTurn{};
public:
	Game() : white(Utils::Color::whitePLayer), black(Utils::Color::blackPlayer) {
		// White starts
		currentTurn = true;
	}
	
	// Return the player that has the current turn
	Player& getCurrentPlayer();

	Player& getNextPlayer();

	// Allow "to" to be expressed in chess notation (ej. f4)
	Board& makeMove(Utils::enumPieces pt, U64 from, U64 to);

};

#endif
