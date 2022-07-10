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
Board& Game::makeMove(Utils::enumPieces pt, U64 from, U64 to) {
	Utils::Color color = getCurrentPlayer().getPlayerColor();

	// Get all the given pieces of type from a player
	U64 ptPieces{this->m_Board.getPieceSetOfAGivenPlayer(pt, color)};	
	U64 pieceToMove{ptPieces & from};

	// Delete the old position of the piece
	ptPieces = (ptPieces ^ pieceToMove);

	// TODO: Check if movement is valid
	// Set the new position
	ptPieces = (ptPieces | to);

	this->m_Board.updateBoard(pt, color, ptPieces);
	

	return this->m_Board;
}
