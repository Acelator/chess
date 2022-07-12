#include "game.h"

Player& Game::getCurrentPlayer() {
	if(currentTurn) {
		return this->white;
	} else {
		return this->black;
	}
}

Player& Game::getNextPlayer() {
	if(!currentTurn) {
		return this->white;
	} else {
		return this->black;
	}
}

// Do we need to return the board?
U64 Game::makeMove(Utils::enumPieces pt, std::uint_fast8_t from, std::uint_fast8_t to, Utils::flagsType moveType) {
	// Get all the given pieces of type from a player
	//U64 ptPieces{this->m_Board.getPieceSetOfAGivenPlayer(pt, color)};
	//U64 pieceToMove{ptPieces & from};

	// Delete the old position of the piece
	//ptPieces = (ptPieces ^ pieceToMove);

	// TODO: Check if movement is valid
	// Set the new position
	//ptPieces = (ptPieces | to);

	//this->m_Board.updateBoard(pt, color, ptPieces);
	Move move = Move(pt, getCurrentPlayer(), from, to, moveType);
	this->m_Board.updateBoard(move, getCurrentPlayer());
	return this->m_Board.getCompleteBoard();
}
