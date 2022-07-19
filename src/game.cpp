#include "game.h"

void Game::newTurn() {
	this->turnCount++;
	this->currentTurn = (!this->currentTurn);
}

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

void Game::determineMovementType(Move &move) {
	auto pt = move.getPieceType();

	bool capture{false};
	bool castle{false};
	
	// Get a bitboard of the current player
	U64 currentPlayerBoard = this->m_board.getAllPiecesOfAGivenPlayer(this->getCurrentPlayer());
	U64 otherPlayerBoard = this->m_board.getAllPiecesOfAGivenPlayer(this->getNextPlayer());

	U64 toSquare = static_cast<std::uint_fast64_t>(1) << move.getTo();

	// Determine if is castle
	// Right now we aren't able to support both sides independely
	if(this->getCurrentPlayer().canPlayerCastle()) {
		if((pt == Utils::enumPieces::rook) || (pt == Utils::enumPieces::king)) {
			if (pt == Utils::enumPieces::rook) {
				// The piece must be moved to the king
				U64 bitboardOfKings{this->m_board.getPieceSet(Utils::enumPieces::king)};
				U64 kingBitboard{bitboardOfKings & currentPlayerBoard};

				if((toSquare & kingBitboard) != 0) {
					castle = true;
				}
			} else {
				// King
				// The piece must be moved to the rook
				U64 bitboardOfRooks{this->m_board.getPieceSet(Utils::enumPieces::rook)};
				U64 rookBitboard{bitboardOfRooks & currentPlayerBoard};

				if((toSquare & rookBitboard) != 0) {
					castle = true;
				}
			}
		}
	}

	// Determine if is capture
	if((toSquare & otherPlayerBoard) != 0) {
		capture = true;
	}
	move.setUpFlags(castle, capture);
}

// Allow to pass piece to promote to
U64 Game::makeMove(Utils::enumPieces pt, std::uint_fast8_t from, std::uint_fast8_t to) {
	// Get all the given pieces of type from a player
	//U64 ptPieces{this->m_Board.getPieceSetOfAGivenPlayer(pt, color)};
	//U64 pieceToMove{ptPieces & from};

	// Delete the old position of the piece
	//ptPieces = (ptPieces ^ pieceToMove);

	// Set the new position
	//ptPieces = (ptPieces | to);

	//this->m_Board.updateBoard(pt, color, ptPieces);
	Move move = Move(pt, getCurrentPlayer(), from, to);
	this->determineMovementType(move);
	
	// Make param constants
	MoveValidator validator = MoveValidator(this->m_board, move, this->getCurrentPlayer());
	bool isValid = validator.validate();
	std::cout << "Movement is: " << std::boolalpha << isValid << '\n';
	
	if(isValid) {
		this->m_board.updateBoard(move, getCurrentPlayer());
		this->newTurn();
		return this->m_board.getCompleteBoard();
	} else {
		return 0;
	}
}
