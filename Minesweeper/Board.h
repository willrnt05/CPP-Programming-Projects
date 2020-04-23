#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include "Tile.h"
#include <SFML/Graphics.hpp>

using namespace std;

class Board
{
public:

	bool debugMode;

	bool gameLost;

	bool gameWon;

	int numRemainingMines;

	Tile completeBoard[18][27];

	void SetBoard(string inputFile);

	void PrintBoard(sf::RenderWindow& W);

	void GetTileCounts();

	void FlagTile(int x, int y);

	bool StandAloneEmpties(Board& B);

	void LeftClickTile(int x, int y);

	void ShowAllMines();

	bool CheckWin();

	void SetRandomBoard();

	//Still Need to Get Working
	void PrintMineCount(sf::RenderWindow& W);
};

