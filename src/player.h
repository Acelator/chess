#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <vector>
#include <map>

#include "utils/utils.h"

class Player {
    Utils::Color m_color;
    bool canCastle{true};

    std::vector<Utils::enumPieces> m_lostPieces{};
public:
    Player(Utils::Color color) : m_color(color) {};
    // Determine the problem
    // Player(Player& pj) : m_color(pj.getPlayerColor()) {};

    Utils::Color getPlayerColor();

    void disallowCastle();

    bool canPlayerCastle() const;

    void newLostPiece(Utils::enumPieces pt);

    std::vector<Utils::enumPieces> getLostPieces();
};

#endif
