#include "moveValidator.h"

bool MoveValidator::validate() {
	// Check if the piece is in the starting position
	// TODO: Check both rook and king if castle
	U64 pieceBoardOfCurrentPlayer{this->board.getPieceSetOfAGivenPlayer(move.getPieceType(), player)};

	U64 piece = (0x1 << move.getFrom());
	bool condition = ((piece & pieceBoardOfCurrentPlayer) != 0);

	if (!condition) {
		// The piece is not there
		// TODO: Add exception
		return false;
	}

	switch (move.getFlags()) {
		case (Utils::flagsType::quietMove): {
			// MoveValidator.isCheck();
			std::vector<Utils::enumSquare> path{};
			try {
				path = this->calculatePath();
				// movement board
				// Represents the path that the piece follow
				U64 movementBoard{};
				for (auto i : path) {
					U64 currentSquare = (0x1 << i);
					movementBoard = (movementBoard | currentSquare);
				}
				
				for (int i{0}; i < static_cast<int>(path.size()); i++) {

				}

			} catch (int x) {
				// TODO: Document possible exceptions
				if (x == -1) {
					return false;
				}
			}
			break;
		}
		case (Utils::flagsType::doublePawnPush): {
			break;
		}
		case (Utils::flagsType::kingCastle):
		case (Utils::flagsType::queenCastle): {
			break;
		}
		case (Utils::flagsType::capture):
		case (Utils::flagsType::epCapture): {
			break;
		}
		case (Utils::flagsType::knightPromotion):
		case (Utils::flagsType::bishopPromotion):
		case (Utils::flagsType::rookPromotion):
		case (Utils::flagsType::queenPromotion): {
			break;
		}
		case (Utils::flagsType::knightPromoAndCapture):
		case (Utils::flagsType::bishopPromoAndCapture):
		case (Utils::flagsType::rookPromoAndCapture):
		case (Utils::flagsType::queenPromoAndCapture): {
			break;
			
		}
	}
	return  true;
}

std::vector<Utils::enumSquare> MoveValidator::calculatePath() {
	auto pt = move.getPieceType();
	std::vector<Utils::enumSquare> path{};

	// Use switch
	if(pt == Utils::enumPieces::pawn) {
		// Determine the file of the starting and final position
		int startingFile = move.mapIntFromLERFnotation(move.getFrom());
		int finalFile{move. mapIntFromLERFnotation(move.getTo())};

		// Diagonal movement
		// TODO: Check that the movement is not more than one square
		if(startingFile != finalFile) {
			if ((finalFile - startingFile == 1 ) || (startingFile - finalFile == 1)) {
				path.push_back(static_cast<Utils::enumSquare>(move.getTo()));
				return path;
			} else {
				// Maybe create a class to represent the exception??
				// Temporally
				throw -1;
			}
		} else { // Straight line
			 path.push_back(static_cast<Utils::enumSquare>(move.getTo()));
			 return path;
		}
	} else if (pt == Utils::enumPieces::bishop) {

	} else if (pt == Utils::enumPieces::knight) {
		
	} else if (pt == Utils::enumPieces::rook) {

	} else if (pt == Utils::enumPieces::queen) {

	} else if (pt == Utils::enumPieces::king) {

	}
	return path;
}
