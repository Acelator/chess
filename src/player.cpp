#include "player.h"

Utils::Color Player::getPlayerColor() {
    return this->m_color;
}

// Castle
void Player::disallowCastle() {
    this->canCastle = false;
}

bool Player::canPlayerCastle() const {
    return this->canCastle;
}

void Player::newLostPiece(Utils::enumPieces pt) {
    this->m_lostPieces.push_back(pt);
}

std::vector<Utils::enumPieces> Player::getLostPieces() {
    return this->m_lostPieces;
}
