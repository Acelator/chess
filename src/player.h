#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <vector>
#include <map>

#include "utils/utils.h"

class Player{
	Utils::Color m_color;

public:
	Player(Utils::Color color) : m_color(color){};
	// Determine the problem
	// Player(Player& pj) : m_color(pj.getPlayerColor()) {};

	Utils::Color getPlayerColor();

};

#endif
