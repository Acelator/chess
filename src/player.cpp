#include "player.h"

Utils::Color Player::getPlayerColor() {
	return this->m_color;
}

// Castle
void Player::disallowCastle() {
	this->canCastle = false;
}

bool Player::canPlayerCastle() {
	return this->canCastle;
}
