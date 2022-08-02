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

bool Player::isPlayerUnderCheck() const {
    return this->underCheck;
}

void Player::updateCheckStatus(bool check) {
    this->underCheck = check;
}

// Players
Player &Players::getCurrentPlayer() {
    if (m_currentTurn) {
        return this->m_white;
    } else {
        return this->m_black;
    }
}

Player &Players::getNextPlayer() {
    if (!m_currentTurn) {
        return this->m_white;
    } else {
        return this->m_black;
    }
}

Player &Players::getWhitePlayer() {
    return this->m_white;
}

Player &Players::getBlackPlayer() {
    return this->m_black;
}
