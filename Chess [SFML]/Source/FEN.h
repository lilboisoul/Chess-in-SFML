#pragma once
#include "Entities/Board.h"
#include <string>
#include <vector>
class FEN
{
public:
	FEN();
	FEN(std::string _fenString);
	~FEN() {};
	
	void ImportFEN(std::string filename);
	//void ExportFEN(Board& board) {};
	void ConvertFEN(std::string fenString);

	std::string GetPieces();
	std::string GetCurrentPlayer();
	std::string GetCastlingRights();
	std::string GetEnPassantMove();
	std::string GetDrawMoves();
	std::string GetTotalMoves();


private:
	std::string fenString;
	std::vector<std::string> fenSplit;
	std::string VerifyFEN(std::string fen);
};

