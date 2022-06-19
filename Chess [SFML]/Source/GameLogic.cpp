#include "GameLogic.h"
#include "Move.h"
#include <iostream>
#include "Entities/Pieces/Pieces.h"
#include "FEN.h"
void GameLogic::SetBoardPtr(Board* _boardPtr)
{
	boardPtr = _boardPtr;
}
void GameLogic::SetCastlingVariables(FEN fen)
{
	if (fen.GetCastlingRights()[0] != '-')
	{
		for (int i = 0; i < fen.GetCastlingRights().size(); i++)
		{
			char temp = fen.GetCastlingRights()[i];
			if (temp == 'k') SetWhiteKingCastleKingside(true);
			if (temp == 'q') SetWhiteKingCastleQueenside(true);
			if (temp == 'K') SetBlackKingCastleKingside(true);
			if (temp == 'Q') SetBlackKingCastleQueenside(true);
		}
	}
	else
	{
		SetWhiteKingCastleKingside(false);
		SetWhiteKingCastleQueenside(false);
		SetBlackKingCastleKingside(false);
		SetBlackKingCastleQueenside(false);
	}
}

bool IsPawn(Square& square)
{
	if (square.GetPiecePtr()->GetID() == 'p' || square.GetPiecePtr()->GetID() == 'P')
		return true;
	return false;
}
bool IsPromotionSquare(Square& square)
{
	if (square.GetBoardPos()[1] - 48 == 8 || square.GetBoardPos()[1] - 48 == 1)
		return true;
	return false;
}
std::unique_ptr<Piece> PromotePawn(App* appPtr, Square& squareHovered, char playerChoice)
{
	Color player_color = squareHovered.GetPiecePtr()->GetColor();
	std::string boardPos = squareHovered.GetBoardPos();
	switch (playerChoice)
	{
	case 'q':
		if (player_color == Color::WHITE)
		{
			return std::make_unique<Queen>(appPtr, player_color, boardPos, 'q');
		}
		return std::make_unique<Queen>(appPtr, player_color, boardPos, 'Q');

	case 'n':
		if (player_color == Color::WHITE)
		{
			return std::make_unique<Knight>(appPtr, player_color, boardPos, 'n');
		}
		return std::make_unique<Knight>(appPtr, player_color, boardPos, 'N');

	case 'b':
		if (player_color == Color::WHITE)
		{
			return std::make_unique<Bishop>(appPtr, player_color, boardPos, 'b');
		}
		return std::make_unique<Bishop>(appPtr, player_color, boardPos, 'B');

	case 'r':
		if (player_color == Color::WHITE)
		{
			return std::make_unique<Rook>(appPtr, player_color, boardPos, 'r');
		}
		return std::make_unique<Rook>(appPtr, player_color, boardPos, 'R');

	}

}
void GameLogic::PawnPromotionManager(App* appPtr, Square& square)
{
	if (IsPawn(square))
	{
		if (IsPromotionSquare(square))
		{
			char playerChoice = 'q';

			square.SetPiece(PromotePawn(appPtr, square, playerChoice));
		}
	}
}

std::vector<std::pair<int, int>> GameLogic::ValidateCastlingMoves(Square& square, std::vector<std::pair<int, int>> moves)
{
	if (square.GetPiecePtr()->HasMoved() || (GetCurrentPlayer() == Color::WHITE && whiteCastled) || (GetCurrentPlayer() == Color::BLACK && blackCastled))
	{
		return moves;
	}
	std::string boardPos = square.GetBoardPos();
	int x = boardPos[0] - 96;
	int y = boardPos[1] - 48;
	std::pair<int, int> kingsideCastleMove = { boardPos[0] - 96 + 2, boardPos[1] - 48}; //moving two squares to the right
	std::pair<int, int> queensideCastleMove = { boardPos[0] - 96 - 2, boardPos[1] - 48}; //moving two squares to the left
	std::vector<std::pair<int, int>> attackedSquares;
	if (GetCurrentPlayer() == Color::WHITE)
	{
		bool isNotAttacked = true;
		attackedSquares = GetSquaresPlayerAttacks(*GetBoardPtr(), Color::BLACK);
		for (auto [x, y] : attackedSquares)
		{
			GetBoardPtr()->arrayOfSquares[x - 1][y - 1]->SetAttacked(true);
		}

		if (canWhiteCastleKingside
			&& !GetBoardPtr()->arrayOfSquares[x][y - 1]->GetPiecePtr() && !GetBoardPtr()->arrayOfSquares[x][y - 1]->IsAttacked()
			&& !GetBoardPtr()->arrayOfSquares[x + 1][y - 1]->GetPiecePtr() && !GetBoardPtr()->arrayOfSquares[x + 1][y - 1]->IsAttacked()
			&& GetBoardPtr()->arrayOfSquares[x + 2][y - 1]->GetPiecePtr()->GetID() == 'r' && !GetBoardPtr()->arrayOfSquares[x + 2][y - 1]->GetPiecePtr()->HasMoved())
			{
				moves.push_back(kingsideCastleMove);
			}
		if (canWhiteCastleQueenside
			&& !GetBoardPtr()->arrayOfSquares[x - 2][y-1]->GetPiecePtr() && !GetBoardPtr()->arrayOfSquares[x - 2][y - 1]->IsAttacked()
			&& !GetBoardPtr()->arrayOfSquares[x - 3][y-1]->GetPiecePtr() && !GetBoardPtr()->arrayOfSquares[x - 3][y - 1]->IsAttacked()
			&& !GetBoardPtr()->arrayOfSquares[x - 4][y-1]->GetPiecePtr() && !GetBoardPtr()->arrayOfSquares[x - 4][y - 1]->IsAttacked()
			&& GetBoardPtr()->arrayOfSquares[x - 5][y - 1]->GetPiecePtr()->GetID() == 'r' && !GetBoardPtr()->arrayOfSquares[x - 5][y - 1]->GetPiecePtr()->HasMoved())
			{
				moves.push_back(queensideCastleMove);
			}
		for (auto [x, y] : attackedSquares)
		{
			GetBoardPtr()->arrayOfSquares[x-1][y-1]->SetAttacked(false);
		}
		
	}
	else 
	{
		bool isNotAttacked = true;
		attackedSquares = GetSquaresPlayerAttacks(*GetBoardPtr(), Color::WHITE);
		for (auto [x, y] : attackedSquares)
		{
			GetBoardPtr()->arrayOfSquares[x - 1][y - 1]->SetAttacked(true);
		}

		if (canBlackCastleKingside
			&& !GetBoardPtr()->arrayOfSquares[x][y - 1]->GetPiecePtr() && !GetBoardPtr()->arrayOfSquares[x][y - 1]->IsAttacked()
			&& !GetBoardPtr()->arrayOfSquares[x + 1][y - 1]->GetPiecePtr() && !GetBoardPtr()->arrayOfSquares[x + 1][y - 1]->IsAttacked()
			&& GetBoardPtr()->arrayOfSquares[x + 2][y - 1]->GetPiecePtr()->GetID() == 'R' && !GetBoardPtr()->arrayOfSquares[x + 2][y - 1]->GetPiecePtr()->HasMoved())
		{
			moves.push_back(kingsideCastleMove);
		}
		if (canBlackCastleQueenside
			&& !GetBoardPtr()->arrayOfSquares[x - 2][y - 1]->GetPiecePtr() && !GetBoardPtr()->arrayOfSquares[x - 2][y - 1]->IsAttacked()
			&& !GetBoardPtr()->arrayOfSquares[x - 3][y - 1]->GetPiecePtr() && !GetBoardPtr()->arrayOfSquares[x - 3][y - 1]->IsAttacked()
			&& !GetBoardPtr()->arrayOfSquares[x - 4][y - 1]->GetPiecePtr() && !GetBoardPtr()->arrayOfSquares[x - 4][y - 1]->IsAttacked()
			&& GetBoardPtr()->arrayOfSquares[x - 5][y - 1]->GetPiecePtr()->GetID() == 'R' && !GetBoardPtr()->arrayOfSquares[x - 5][y - 1]->GetPiecePtr()->HasMoved())
		{
			moves.push_back(queensideCastleMove);
		}
		for (auto [x, y] : attackedSquares)
		{
			GetBoardPtr()->arrayOfSquares[x - 1][y - 1]->SetAttacked(false);
		}

	}
	return moves;
}
void GameLogic::Castle(int side, Move& moveManager, Square& square)
{

	if (GetCurrentPlayer() == Color::WHITE)
	{
		if (side > 0)
		{
			WhiteCastled();
			GetBoardPtr()->arrayOfSquares[5][0]->SetPiece(std::move(GetBoardPtr()->arrayOfSquares[7][0]->GetPiecePtr()));
			GetBoardPtr()->arrayOfSquares[5][0]->GetPiecePtr()->Moved();
			return;
		}
		WhiteCastled();
		GetBoardPtr()->arrayOfSquares[3][0]->SetPiece(std::move(GetBoardPtr()->arrayOfSquares[0][0]->GetPiecePtr()));
		GetBoardPtr()->arrayOfSquares[3][0]->GetPiecePtr()->Moved();
		return;
	}
	if (side > 0)
	{
		BlackCastled();
		GetBoardPtr()->arrayOfSquares[5][7]->SetPiece(std::move(GetBoardPtr()->arrayOfSquares[7][7]->GetPiecePtr()));
		GetBoardPtr()->arrayOfSquares[5][7]->GetPiecePtr()->Moved();
		return;
	}
	BlackCastled();
	GetBoardPtr()->arrayOfSquares[3][7]->SetPiece(std::move(GetBoardPtr()->arrayOfSquares[0][7]->GetPiecePtr()));
	GetBoardPtr()->arrayOfSquares[3][7]->GetPiecePtr()->Moved();
	return;
	
}
GameLogic::GameLogic(GameMode _gamemode, FEN fenString) : currentGameMode(_gamemode)
{
	SetCurrentPlayer(fenString.GetCurrentPlayer());
	SetCastlingVariables(fenString);
	SetDrawMoves(std::stoi(fenString.GetDrawMoves()));
	SetTotalMoves(std::stoi(fenString.GetTotalMoves()));
}

Board* GameLogic::GetBoardPtr()
{
	return boardPtr;
}

GameMode GameLogic::GetGameMode()
{
	return currentGameMode;
}

Color GameLogic::GetCurrentPlayer()
{
	return this->currentPlayer;
}

bool GameLogic::CanWhiteCastleKingside()
{
	return canWhiteCastleKingside;
}

bool GameLogic::CanWhiteCastleQueenside()
{
	return canWhiteCastleQueenside;
}

bool GameLogic::CanBlackCastleKingside()
{
	return canBlackCastleKingside;
}

bool GameLogic::CanBlackCastleQueenside()
{
	return canBlackCastleQueenside;
}


//
//std::string GameLogic::GetEnPassantMove()
//{
//	return enPassantMove;
//}

int GameLogic::GetDrawMoves()
{
	return drawMoves;
}

int GameLogic::GetTotalMoves()
{
	return totalMoves;
}

void GameLogic::SetCurrentPlayer(std::string player)
{
	if (player == "w")
	{
		this->currentPlayer = Color::WHITE;
	}
	else
	{
		this->currentPlayer = Color::BLACK;
	}
}

void GameLogic::SetGameState(GameState state)
{
	currentGameState = state;
}

void GameLogic::SetWhiteKingCastleKingside(bool _val)
{
	canWhiteCastleKingside = _val;
}

void GameLogic::SetWhiteKingCastleQueenside(bool _val)
{
	canWhiteCastleQueenside = _val;
}

void GameLogic::SetBlackKingCastleKingside(bool _val)
{
	canBlackCastleKingside = _val;
}

void GameLogic::SetBlackKingCastleQueenside(bool _val)
{
	canBlackCastleQueenside = _val;
}

void GameLogic::WhiteCastled()
{
	whiteCastled = true;
	canWhiteCastleKingside = false;
	canWhiteCastleQueenside = false;
}
void GameLogic::BlackCastled()
{
	blackCastled = true;
	canBlackCastleKingside = false;
	canBlackCastleQueenside = false;
}


void GameLogic::SetDrawMoves(unsigned int _moves)
{
	this->drawMoves = _moves;
}

void GameLogic::SetTotalMoves(unsigned int _moves)
{
	this->totalMoves = _moves;
}

bool GameLogic::CheckMoveLegality(Square& destination, std::vector<std::pair<int, int>> moves)
{
	
	for (int i = 0; i < moves.size(); i++) {
		if (destination.GetBoardPos()[0] - 96 == moves[i].first 
			&& destination.GetBoardPos()[1] - 48 == moves[i].second) {
			return true;
		}
	}
	return false;
}

std::vector<std::pair<int, int>> GameLogic::ValidateMoves(Square* currentSquare, Move& moveManager, std::vector<std::pair<int, int>> moves)
{
	Color playerColor;
	GetCurrentPlayer() == Color::WHITE ? playerColor = Color::BLACK : playerColor = Color::WHITE;
	std::vector<std::pair<int, int>> validatedMoves;
	std::unique_ptr<Piece> temp = nullptr;

	for (auto [x, y] : moves)
	{
		temp = moveManager.SimulateMove(*currentSquare, *GetBoardPtr()->arrayOfSquares[x - 1][y - 1]);
		if (!IsPlayerKingChecked(*GetBoardPtr(), GetCurrentPlayer()))
		{
			validatedMoves.push_back({ x, y });
		}
		moveManager.MakeMove(*GetBoardPtr()->arrayOfSquares[x - 1][y - 1], *currentSquare);
		if (temp)
		{
			GetBoardPtr()->arrayOfSquares[x - 1][y - 1]->SetPiece(std::move(temp));
			temp = nullptr;
		}
	}	
	return validatedMoves;
}

std::string GameLogic::GetKingBoardPos(Board& board, Color player)
{
	char id;
	player == Color::WHITE ? id = 'k' : id = 'K';
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			Square* sqr = board.arrayOfSquares[i][j];
			if (sqr->GetPiecePtr() != nullptr) {
				if ((sqr->GetPiecePtr()->GetID() == id && GetCurrentPlayer() == player))
					return sqr->GetPiecePtr()->GetBoardPos();
				
			}
		}
	}
	return "a1";
}

std::vector<std::pair<int, int>> GameLogic::GetSquaresPlayerAttacks(Board& board, Color playerColor)
{
	std::vector<std::pair<int, int>> pieceLegalMoves;
	std::vector<std::pair<int, int>> attackedSquares;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pieceLegalMoves.resize(0);
			if (board.arrayOfSquares[i][j]->GetPiecePtr() != nullptr) {
				if (board.arrayOfSquares[i][j]->GetPiecePtr()->GetColor() == playerColor) {
					pieceLegalMoves = board.arrayOfSquares[i][j]->GetPiecePtr()->GetAttackedSquares(board);
					for (auto i : pieceLegalMoves) attackedSquares.push_back(i);
				}

			}
		}
	}
	return attackedSquares;
}

std::vector<std::pair<int, int>> GameLogic::GetPlayerValidMoves(Board& board, Move& moveManager, Color playerColor)
{
	std::vector<std::pair<int, int>> pieceLegalMoves;
	std::vector<std::pair<int, int>> validMoves;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pieceLegalMoves.resize(0);
			if (board.arrayOfSquares[i][j]->GetPiecePtr() != nullptr) {
				if (board.arrayOfSquares[i][j]->GetPiecePtr()->GetColor() == playerColor) {
					pieceLegalMoves = board.arrayOfSquares[i][j]->GetPiecePtr()->GetPseudoLegalMoves(board);
					pieceLegalMoves = ValidateMoves(board.arrayOfSquares[i][j], moveManager, pieceLegalMoves);
					for (auto i : pieceLegalMoves) validMoves.push_back(i);
				}

			}
		}
	}
	
	return validMoves;
}

bool GameLogic::IsPlayerKingChecked(Board& board, Color player)
{
	Color enemyPlayer;
	player == Color::WHITE ? enemyPlayer = Color::BLACK : enemyPlayer = Color::WHITE;

	std::string allyKingBoardPos= GetKingBoardPos(board, player);
	std::vector<std::pair<int, int>> allPseudoLegalMoves = GetSquaresPlayerAttacks(board, enemyPlayer);

	for (auto [x, y] : allPseudoLegalMoves)
	{
		if (x == allyKingBoardPos[0] - 96 
			&& y == allyKingBoardPos[1] - 48) {
			return true;
		}
	}
	return false;
}

void GameLogic::CheckGameState(Board& board, Move& moveManager)
{
	whiteKingChecked = false;
	blackKingChecked = false;
	SetGameState(GameState::NORMAL);
	if (IsPlayerKingChecked(board, Color::WHITE))
	{
		whiteKingChecked = true;
		SetGameState(GameState::CHECK);
		std::cout << "check";
	}

	if (IsPlayerKingChecked(board, Color::BLACK))
	{
		blackKingChecked = true;
		SetGameState(GameState::CHECK);
		std::cout << "check";
	}
	if ((!whiteKingChecked && GetPlayerValidMoves(board, moveManager, Color::WHITE).size() == 0)
		|| (!blackKingChecked && GetPlayerValidMoves(board, moveManager, Color::BLACK).size() == 0))
	{
		SetGameState(GameState::STALEMATE);
		std::cout << "stalemate";
		return;
		//stalemate
	}
	if (whiteKingChecked && GetPlayerValidMoves(board, moveManager, Color::WHITE).size() == 0)
	{
		SetGameState(GameState::CHECKMATE);
		std::cout << "checkmate";
		return;
		//black won by checkmate
	}
	if (blackKingChecked && GetPlayerValidMoves(board, moveManager, Color::BLACK).size() == 0)
	{
		SetGameState(GameState::CHECKMATE);
		std::cout << "checkmate";
		return;
		//white won by checkmate
	}


}
