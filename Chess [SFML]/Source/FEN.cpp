#include "FEN.h"
#include "Entities/Board.h"
#include <filesystem>
#include <fstream>
FEN::FEN()
{
	fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	ConvertFEN(fenString);
}
FEN::FEN(std::string _fenString) : fenString(_fenString)
{
	if (fenString.empty())
	{
		fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	}
	ConvertFEN(fenString);
}

void FEN::ImportFEN(std::string filename)
{
	std::filesystem::path path = std::filesystem::current_path().append(filename);
	if (std::filesystem::exists(path)) {
		std::ifstream plik(path);
		std::getline(plik, fenString);
	}
}

void FEN::ConvertFEN(std::string fenString)
{
	for (int i = 0; i < 6; i++) fenSplit.push_back("");
	int tempIndex = 0;
	//extracting piece-portion of FEN
	while (fenString[tempIndex] != ' ') {
		fenSplit[0] += fenString[tempIndex];
		tempIndex++;
	}
	tempIndex++;
	//extracting which player moves on the next turn
	fenSplit[1] = fenString[tempIndex];
	tempIndex += 2;

	//extracting castling rights
	if (fenString[tempIndex] == '-')
	{
		fenSplit[2].append("-");
		tempIndex += 2;
	}
	else {
		while (fenString[tempIndex] != ' ' && (fenString[tempIndex] == 'k' || fenString[tempIndex] == 'q' || fenString[tempIndex] == 'K' || fenString[tempIndex] == 'Q'))
		{
			fenSplit[2] += fenString[tempIndex];
			tempIndex++;
		}
		tempIndex++;
	}
	//extracting en-passant move
	if (fenString[tempIndex] == '-')
	{
		fenSplit[3].append("-");
		tempIndex += 2;
	}
	else {
		while (fenString[tempIndex] != ' ')
		{
			fenSplit[3] += fenString[tempIndex];
			tempIndex++;
		}
		tempIndex++;
	}
	//draw moves
	while (fenString[tempIndex] != ' ')
	{
		fenSplit[4] += fenString[tempIndex];
		tempIndex++;
	}
	tempIndex++;

	//total moves
	while (tempIndex <= fenString.size())
	{
		fenSplit[5] += fenString[tempIndex];
		tempIndex++;
	}

}

std::string FEN::GetPieces()
{
	return fenSplit[0];
}

std::string FEN::GetCurrentPlayer()
{
	return fenSplit[1];
}

std::string FEN::GetCastlingRights()
{
	return fenSplit[2];
}

std::string FEN::GetEnPassantMove()
{
	return fenSplit[3];
}

std::string FEN::GetDrawMoves()
{
	return fenSplit[4];
}

std::string FEN::GetTotalMoves()
{
	return fenSplit[5];
}
