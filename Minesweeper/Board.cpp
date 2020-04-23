#include "Board.h"

using namespace std;

//WORKING!!!
void Board::SetBoard(string inputFile)
{
	//debugMode = false;
	gameLost = false;

	//Actually Need to use a count mines fcn
	numRemainingMines = 0;

	for (int i = 0; i < 27; ++i)
	{
		completeBoard[0][i].isMine = false;
	}
	for (int i = 0; i < 27; ++i)
	{
		completeBoard[17][i].isMine = false;
	}
	for (int i = 0; i < 18; ++i)
	{
		completeBoard[i][0].isMine = false;
		completeBoard[i][26].isMine = false;
	}
	
	ifstream fileName(inputFile);
	//While not eof
	int currentLine = 1;
	while (!fileName.eof())
	{
		string tempString;

		getline(fileName, tempString);
		
		for (int i = 0; i < 25; ++i)
		{
			if (tempString[i] == '1') { 
				
				completeBoard[currentLine][i + 1].isMine = true;
				numRemainingMines += 1;
			}
			else { 
				
				completeBoard[currentLine][i + 1].isMine = false; 
			}
			completeBoard[currentLine][i + 1].hasBeenClicked = false;
			completeBoard[currentLine][i + 1].isFlagged = false;
		}
		currentLine += 1;

		GetTileCounts();
	}
	//cout << numRemainingMines << endl;
}

//WORKING!!!
void Board::PrintBoard(sf::RenderWindow& W)
{
	//Hidden Tile
	sf::Texture hiddenTileTexture;
	hiddenTileTexture.loadFromFile("images/tile_hidden.png");
	sf::Sprite hiddenTile(hiddenTileTexture);

	//Empty Tile
	sf::Texture revealedTileTexture;
	revealedTileTexture.loadFromFile("images/tile_revealed.png");
	sf::Sprite revealedTile(revealedTileTexture);

	//Mine Load
	sf::Texture mineTexture;
	mineTexture.loadFromFile("images/mine.png");
	sf::Sprite mine(mineTexture);

	//Flag Load
	sf::Texture flagTexture;
	flagTexture.loadFromFile("images/flag.png");
	sf::Sprite flag(flagTexture);

	//Still Playing Face
	sf::Texture playingTexture;
	playingTexture.loadFromFile("images/face_happy.png");
	sf::Sprite playing(playingTexture);
	playing.setPosition(352, 512);

	//Lost Game Face
	sf::Texture lostTexture;
	lostTexture.loadFromFile("images/face_lose.png");
	sf::Sprite lost(lostTexture);
	lost.setPosition(352, 512);

	//Winning Face
	sf::Texture winTexture;
	winTexture.loadFromFile("images/face_win.png");
	sf::Sprite win(winTexture);
	win.setPosition(352, 512);

	//Debug Mode Button
	sf::Texture debugTexture;
	debugTexture.loadFromFile("images/debug.png");
	sf::Sprite debug(debugTexture);
	debug.setPosition(496, 512);
	W.draw(debug);

	//Test 1
	sf::Texture test1Texture;
	test1Texture.loadFromFile("images/test_1.png");
	sf::Sprite test1(test1Texture);
	test1.setPosition(560, 512);
	W.draw(test1);

	//Test 2
	sf::Texture test2Texture;
	test2Texture.loadFromFile("images/test_2.png");
	sf::Sprite test2(test2Texture);
	test2.setPosition(624, 512);
	W.draw(test2);

	//Test 3
	sf::Texture test3Texture;
	test3Texture.loadFromFile("images/test_3.png");
	sf::Sprite test3(test3Texture);
	test3.setPosition(688, 512);
	W.draw(test3);


	//Loop through array... Keep track of each 32
	//If it has been clicked, write the number,
	//If it has not been clicked, click on it, change status, report mine

	PrintMineCount(W);

	gameWon = CheckWin();

	if (gameWon == true)
	{
		for (int i = 0; i < 16; ++i)
		{
			for (int j = 0; j < 25; ++j)
			{
				if (completeBoard[i + 1][j + 1].hasBeenClicked == false)
				{
					completeBoard[i + 1][j + 1].isFlagged = true;
				}
			}
		}
		numRemainingMines = 0;

		W.draw(win);
	}
	else if (gameWon == false && gameLost == false)
	{
		W.draw(playing);
	}
	else
	{
		W.draw(lost);
	}


	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{
			//This will need on click function.... If the file is revealed, then do this code
			//If the file is not revealed do not
			//For now just write hidden tile
			sf::Vector2f position(j * 32, i * 32);


			if (completeBoard[i + 1][j + 1].hasBeenClicked == false)
			{
				hiddenTile.setPosition(position);
				W.draw(hiddenTile);
				if (completeBoard[i + 1][j + 1].isMine && debugMode == true)
				{
					mine.setPosition(position);
					W.draw(mine);
				}
			}

			if (completeBoard[i + 1][j + 1].isFlagged == true)
			{
				hiddenTile.setPosition(position);
				flag.setPosition(position);
				W.draw(hiddenTile);
				W.draw(flag);
			}


			if(completeBoard[i+1][j+1].hasBeenClicked == true)
			{
				//Need to reveal all mines if clicked on one
				if (completeBoard[i + 1][j + 1].isMine == true)
				{
					mine.setPosition(position);
					revealedTile.setPosition(position);
					W.draw(revealedTile);
					W.draw(mine);
				}

				else if (completeBoard[i + 1][j + 1].isMine == false)
				{

					//Write function to check how many mines it is against.. If zero for any that are close to it, delete...
					string imageGet = "images/number_";

					sf::Texture numTexture;

					imageGet += to_string(completeBoard[i + 1][j + 1].numMinesTouching);
					imageGet += ".png";

					revealedTile.setPosition(position);
					W.draw(revealedTile);

					if (completeBoard[i + 1][j + 1].numMinesTouching != 0)
					{
						numTexture.loadFromFile(imageGet);
						sf::Sprite num(numTexture);
						num.setPosition(position);
						W.draw(num);
					}
				}
				
			}
		
		}
	
	}
	
}

//WORKING!!!!
void Board::GetTileCounts()
{
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{

			
			if (completeBoard[i + 1][j + 1].isMine == false)
			{
				//Write function to check how many mines it is against.. If zero for any that are close to it, delete...
				int numMines = 0;
				for (int k = j; k <= j + 2; ++k)
				{
					if (completeBoard[i][k].isMine == true) { numMines += 1; }
				}
				if (completeBoard[i + 1][j].isMine == true) {
					numMines += 1;
				}
				if (completeBoard[i + 1][j+2].isMine == true) {
					numMines += 1;
				}
				for (int k = j; k <= j + 2; ++k)
				{
					if (completeBoard[i+2][k].isMine == true) { numMines += 1; }
				}
				completeBoard[i + 1][j + 1].numMinesTouching = numMines;
			}

		}

	}
}

//WORKING!!!!
void Board::FlagTile(int x, int y)
{
	if (completeBoard[y][x].isFlagged == false)
	{
		completeBoard[y][x].isFlagged = true;
		--numRemainingMines;
	}
	else
	{
		completeBoard[y][x].isFlagged = false;
		++numRemainingMines;
	}
}

//WORKING!!!
bool Board::StandAloneEmpties(Board &B)
{
	bool needToGoAgain = false;

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{
			
			if (B.completeBoard[i + 1][j + 1].numMinesTouching == 0 && B.completeBoard[i + 1][j + 1].hasBeenClicked == true
				&&B.completeBoard[i + 1][j + 1].isMine == false)
			{
				//Write function to check how many mines it is against.. If zero for any that are close to it, delete...
				for (int k = j; k <= j + 2; ++k)
				{
					if (B.completeBoard[i][k].hasBeenClicked == false && B.completeBoard[i][k].isFlagged == false) {
						B.completeBoard[i][k].hasBeenClicked = true;
						needToGoAgain = true;
					}
				}
				if (B.completeBoard[i + 1][j].hasBeenClicked == false && B.completeBoard[i + 1][j].isFlagged == false) {
					B.completeBoard[i + 1][j].hasBeenClicked = true;
					needToGoAgain = true;
				}
				if (B.completeBoard[i + 1][j + 2].hasBeenClicked == false && B.completeBoard[i+1][j+2].isFlagged == false) {
					B.completeBoard[i + 1][j + 2].hasBeenClicked = true;
					needToGoAgain = true;
				}
				for (int k = j; k <= j + 2; ++k)
				{
					if (B.completeBoard[i + 2][k].hasBeenClicked == false && B.completeBoard[i+2][k].isFlagged == false) {
						B.completeBoard[i + 2][k].hasBeenClicked = true;
						needToGoAgain = true;
					}
				}
				
			}

		}

	}
	return needToGoAgain;
}

//WORKING!!!
void Board::LeftClickTile(int x, int y)
{
	int arrayX = (int)x / 32 + 1;
	int arrayY = (int)y / 32 + 1;
	//NEED TO MAKE SURE IT IS NOT FLAGGED
	//FOR NOW JUST REVEAL TILE
	if (completeBoard[arrayY][arrayX].isFlagged == false && gameLost == false)
	{
		completeBoard[arrayY][arrayX].hasBeenClicked = true;
		if (completeBoard[arrayY][arrayX].isMine == true)
		{
			ShowAllMines();
			gameLost = true;
		}
	}
	if (y < 576 && y > 512 && x > 352 && x < 416)
	{
		SetRandomBoard();
	}
	if (y < 576 && y > 512 && x > 496 && x <= 560)
	{
		if (debugMode == false) {
			//cout << "Got into the IF " << endl;
			debugMode = true;
		}
		else
		{
			debugMode = false;
		}
	}
	if (y < 576 && y > 512 && x > 560 && x <= 624)
	{
		//cout << "Got into the IF " << endl;
		SetBoard("boards/testboard1.brd");
	}
	if (y < 576 && y > 512 && x > 624 && x <= 688)
	{
		//cout << "Got into the IF " << endl;
		SetBoard("boards/testboard2.brd");
	}
	if (y < 576 && y > 512 && x > 688 && x <= 752)
	{
		//cout << "Got into the IF " << endl;
		SetBoard("boards/testboard3.brd");
	}
	
}

//WORKING!!!
void Board::ShowAllMines()
{
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{
			if (completeBoard[i + 1][j + 1].isMine == true)
			{
				completeBoard[i + 1][j + 1].hasBeenClicked = true;
			}
		}
	}
}

//WORKING!!!
bool Board::CheckWin()
{
	bool temp = true;

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{


			if (completeBoard[i + 1][j + 1].hasBeenClicked == false && completeBoard[i + 1][j + 1].isMine == false)
			{
				temp = false;
			}

		}
	}
	return temp;
}

//WORKING!!!
void Board::SetRandomBoard()
{
	//Relative Setup Borrowed From Debug
	gameLost = false;
	//debugMode = false;

	numRemainingMines = 50;

	int mineStringCount = 0;

	string mineString = "";
	for (int i = 0; i < 400; ++i)
	{
		//Get Random Number .... Add to String.... Deal with later
		mineString += "0";
	}

	while (mineStringCount < 50)
	{
		int a = rand() % 399;
		//cout << a << endl;
		if (mineString[a] == '0')
		{
			mineString[a] = '1';
			mineStringCount += 1;
		}
		else
		{
			//cout << "Got a Repeat: " << endl;
		}
		//cout << mineStringCount << endl;
	}
	
	

	for (int i = 0; i < 27; ++i)
	{
		completeBoard[0][i].isMine = false;
	}
	for (int i = 0; i < 27; ++i)
	{
		completeBoard[17][i].isMine = false;
	}
	for (int i = 0; i < 18; ++i)
	{
		completeBoard[i][0].isMine = false;
		completeBoard[i][26].isMine = false;
	}

	//int tester = 0;
	int currentPoint = 0;
	for (int currentLine = 1; currentLine < 17; ++currentLine)
	{

		for (int i = 1; i < 26; ++i)
		{
			
			//cout << "Current Line: " << currentLine << " X index: " << i << endl;
			//cout << "Trying to Access Index" << (i) * currentLine - 1 << endl;
			if (mineString[currentPoint] == '1') {

				completeBoard[currentLine][i].isMine = true;
				//tester += 1;
			}
			else {

				completeBoard[currentLine][i].isMine = false;
			}
			currentPoint += 1;
			completeBoard[currentLine][i].hasBeenClicked = false;
			completeBoard[currentLine][i].isFlagged = false;
		}
	}
	//cout << "Tester: " << tester << endl;
	


	GetTileCounts();
}

//WORKING!!!
void Board::PrintMineCount(sf::RenderWindow& W)
{
	//- is 11
	map<int, sf::Sprite> digitsMap;

	sf::Texture digitsTexture;
	digitsTexture.loadFromFile("images/digits.png");
	sf::Sprite digits(digitsTexture);

	for (int i = 0; i < 11; ++i)
	{
		digits.setTextureRect(sf::IntRect(i * 21, 0, 21, 32));
		digitsMap[i] = digits;
	}

	

	int numPrintedTiles;

	if (numRemainingMines >= 100 || numRemainingMines <= -100) { numPrintedTiles = 3; }
	else if (numRemainingMines >= 10 || numRemainingMines <= -10) { numPrintedTiles = 2; }
	else { numPrintedTiles = 1; }

	if(numRemainingMines < 0) { numPrintedTiles += 1; }


	string numMines = to_string(numRemainingMines);


	for (int i = 0; i < numPrintedTiles; ++i)
	{
		if (numMines[i] == '-')
		{
			//cout << "Hitting the negative loop" << endl;
			sf::Sprite temp = digitsMap[10];
			temp.setPosition(sf::Vector2f(0, 512));
			W.draw(temp);
		}
		else
		{
			//cout << "Hitting the Positive Loop" << endl;
			//cout << "Trying to Draw " << (int)numMines[i] - 48 << endl;
			sf::Sprite temp = digitsMap[(int)numMines[i] - 48];
			//cout << "Trying to Draw Sprites " << stoi(to_string(numMines[i])) << endl;
	
			
			temp.setPosition(sf::Vector2f(i * 21, 512));
			W.draw(temp);
		}
	}
	
}

//NOTE: Have to ask how debug mode should still work after a loss.
//NOTE: Says "Flagged Tiles cannot be removed in anyway" and 
// "Draw the mines over anything else for Debug Mode"