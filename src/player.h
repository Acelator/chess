#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <vector>
#include <map>

#include "utils/utils.h"

class Player {
    Utils::Color m_color;
    bool canCastle{true};
    bool underCheck{false};

    std::vector<Utils::enumPieces> m_lostPieces{};
public:
    Player(Utils::Color color) : m_color(color) {};
    // Determine the problem
    // Player(Player& pj) : m_color(pj.getPlayerColor()) {};

    Utils::Color getPlayerColor();

    void disallowCastle();

    bool canPlayerCastle() const;

    bool isPlayerUnderCheck() const;

    void updateCheckStatus(bool check);

    void newLostPiece(Utils::enumPieces pt);

    std::vector<Utils::enumPieces> getLostPieces();
};

class Players {
    Player m_white;
    Player m_black;

    // True is m_white, false is m_black
    const bool &m_currentTurn{true};

public:
    explicit Players(const bool &turn) : m_white(Utils::Color::whitePLayer), m_black(Utils::Color::blackPlayer), m_currentTurn(turn) {

    }

    // Return the player that has the current turn
    Player &getCurrentPlayer();

    Player &getNextPlayer();

    Player &getWhitePlayer();

    Player &getBlackPlayer();

};

#endif
