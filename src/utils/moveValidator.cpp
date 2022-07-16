#include "moveValidator.h"

bool MoveValidator::validate() {
	// Check if the piece is in the starting position
	// TODO: Check both rook and king if castle
	U64 pieceBoardOfCurrentPlayer{this->board.getPieceSetOfAGivenPlayer(move.getPieceType(), player)};

	// IMPORTANT
	U64 piece = (static_cast<std::uint_fast64_t>(1) << move.getFrom());
	bool condition = ((piece & pieceBoardOfCurrentPlayer) != 0);

	if (!condition) {
		// The piece is not there
		// TODO: Add exception
		return false;
	}

	// Should we determine the flags or they should be provided by the engine??
	switch (move.getFlags()) {
		case (Utils::flagsType::quietMove):
		case (Utils::flagsType::doublePawnPush): {
			// MoveValidator.isCheck();
			std::vector<Utils::enumSquare> path{};

			try {
				path = this->calculatePath();
			} catch (int x) {
				// TODO: Document possible exceptions
				if (x == -1) {
					return false;
				}
			}
			// Represents the path that the piece follow
			U64 movementBoard{};
			for (auto i : path) {
				U64 currentSquare = (static_cast<std::uint_fast64_t>(1) << i);
				std::cout << "Current: " << currentSquare << '\n';
				movementBoard = (movementBoard | currentSquare);
			}

			std::cout << "complete: " << movementBoard << '\n';
			auto completeBoard{this->board.getCompleteBoard()};

			// No piece intersect during the movement
			if((completeBoard & movementBoard) == 0) {
				return true;
			}
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
		case (Utils::flagsType::rookPromotion):
		case (Utils::flagsType::knightPromotion):
		case (Utils::flagsType::bishopPromotion):
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
	return  false;
}

std::vector<Utils::enumSquare> MoveValidator::calculatePath() {
	auto pt = move.getPieceType();
	std::vector<Utils::enumSquare> path{};

	// Determine the file of the starting and final square
	int startingFile = move.obtainFileFromSquare(move.getFrom());
	int finalFile{move.obtainFileFromSquare(move.getTo())};

	// Use switch
	// TODO: Impement en passant
	if(pt == Utils::enumPieces::pawn) {
		// Diagonal movement
		if(startingFile != finalFile) {
			// TODO: Check if this works
			if(!(move.getFlags() == Utils::flagsType::capture) || !(move.getFlags() == Utils::flagsType::epCapture)) {
				// Piece is trying to go diagonally without capturing a piece
				throw -1;
			}
			if ((std::abs(finalFile - startingFile)) == 1 )  {
				path.push_back(static_cast<Utils::enumSquare>(move.getTo()));
				return path;
			} else {
				// Maybe create a class to represent the exception??
				// Temporally
				// Pawn is trying to go from one file to another two units away
				throw -1;
			}
		} else if (std::abs(move.getTo() - move.getFrom()) == 16) {
			// Double pawn push
			if ((move.obtainRankFromSquare(move.getFrom()) == 2) && (player.getPlayerColor() == Utils::Color::whitePLayer)) {
				path.push_back(static_cast<Utils::enumSquare>(move.getFrom() + 8));
				path.push_back(static_cast<Utils::enumSquare>(move.getTo()));
				return path;
			} else if ((move.obtainRankFromSquare(move.getFrom()) == 7) && (player.getPlayerColor() == Utils::Color::blackPlayer)) {
				path.push_back(static_cast<Utils::enumSquare>(move.getFrom() - 8));
				path.push_back(static_cast<Utils::enumSquare>(move.getTo()));
				return path;
			} else {
				// Pawn isn't in the intial position, so the double push isn't possible
				throw -1;
			}
		} else if (std::abs(move.getTo() - move.getFrom()) > 16) {
			// Pawn is trying to go further than two squares in straight line
			throw -1;
		} else {
			path.push_back(static_cast<Utils::enumSquare>(move.getTo()));
		}
		return path;
	} else if (pt == Utils::enumPieces::bishop) {
		if (startingFile == finalFile) {
			// Bishop move isn't diagonal
			throw -1;
		} else {
			// Compass rose
			// TODO: Improve (Explain why 9 and 7 are used)
			if((std::abs(move.getFrom() - move.getTo()) % 9) == 0) {
				std::cout << ":Sdsadadad\n";
				if(move.getFrom() > move.getTo()) {
					// noEa
					for(int i{move.getFrom() - 9}; i >= move.getTo(); i -= 9) {
						path.push_back(static_cast<Utils::enumSquare>(i));
					}
				} else {
					std::cout << "Cocococn\n";
					// soWe
					for(int i{move.getFrom() + 9}; i <= move.getTo(); i += 9) {
						path.push_back(static_cast<Utils::enumSquare>(i));
					}
				}
			} else if ((std::abs(move.getFrom() - move.getTo()) % 7) == 0) {
				std::cout << "Ppasasad\n";
				if(move.getFrom() > move.getTo()) {
					// noWe
					for(int i{move.getFrom() - 7}; i >= move.getTo(); i -= 7) {
						path.push_back(static_cast<Utils::enumSquare>(i));
					}
				} else {
					// soEa
					for(int i{move.getFrom() + 7}; i <= move.getTo(); i += 7) {
						path.push_back(static_cast<Utils::enumSquare>(i));
					}
				}
			} else {
				throw -1;
			}
		}

	} else if (pt == Utils::enumPieces::knight) {
		
	} else if (pt == Utils::enumPieces::rook) {

	} else if (pt == Utils::enumPieces::queen) {

	} else if (pt == Utils::enumPieces::king) {

	}
	return path;
}
