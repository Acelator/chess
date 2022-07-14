#ifndef CHESS_GAME_H
#define CHESS_GAME_H

// Make sure libraries are only compiled once
#include <cstdint>
#include <iostream>

#include "utils/utils.h"

#include "board.h"
#include "move.h"

#include "utils/moveValidator.h"
#include "player.h"

class Game {
private:
	Player white;
	Player black;
	Board m_Board{};

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
	U64 makeMove(Utils::enumPieces pt, std::uint_fast8_t from, std::uint_fast8_t to, Utils::flagsType moveType);

};

#endif
