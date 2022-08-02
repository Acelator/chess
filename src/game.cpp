#include "game.h"

void Game::newHalfTurn(Move &move) {
    // Check if the fifty-move rule isn't broken
    // If move is number 50 allow the player to determine if a draw must be done
    if (move.isCapture() || move.getPieceType() == Utils::enumPieces::pawn) {
        this->m_fiftyMoveCount = 0;
    } else {
        this->m_fiftyMoveCount++;
    }
    if (this->m_fiftyMoveCount == 75) {
        // Draw is mandatory applied (Seventy-five-move rule)
        throw -1;

    }
    this->m_halfTurnCount++;
    this->m_currentTurn = (!this->m_currentTurn);
}

// Allow to pass piece to promote to
// TODO: Update to UCI (Universal Chess Interface)
U64 Game::makeMove(Utils::enumPieces pt, std::uint_fast8_t from, std::uint_fast8_t to) {
    Move move = Move(pt, players.getCurrentPlayer(), from, to);
    determineMovementType(players.getCurrentPlayer(), m_board, move);

    // Make param constants
    MoveValidator validator = MoveValidator(this->m_board, move, players.getCurrentPlayer());
    bool isValid = validator.validate(true);
    std::cout << "Movement is: " << std::boolalpha << isValid << '\n';

    if (isValid) {
        this->m_board.updateBoard(move, players);
        m_board.saveAttackVector(players.getCurrentPlayer(), calculateInitialAttackVector(players.getCurrentPlayer(), m_board));

        // Update check status
        U64 otherPlayerKingBitboard{m_board.getAllPiecesOfAGivenPlayer(players.getNextPlayer()) & m_board.getPieceSet(Utils::enumPieces::king)};
        if ((otherPlayerKingBitboard & m_board.getPlayerAttackVector(players.getCurrentPlayer())) != 0) {
            std::cout << "Player: " << players.getNextPlayer().getPlayerColor() << " is under check\n";

            // Check if the move has lead to checkmate
            if (isCheckMate(players.getNextPlayer(), players.getCurrentPlayer(), this->m_board)) {
                std::cout << "Checkmated\n";
                throw -2;
            }
            players.getNextPlayer().updateCheckStatus(true);
        } else {
            players.getNextPlayer().updateCheckStatus(false);
        }

        try {
            this->newHalfTurn(move);
        } catch (int x) {
            // Draw
            throw -1;
        }
        std::cout << this->m_board << '\n';
        std::cout << "-------------------------\n";
        return this->m_board.getCompleteBoard();
    } else {
        std::cout << "-------------------------\n";
        return 0;
    }
}

