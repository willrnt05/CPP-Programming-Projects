#pragma once

class Tile
{
public:
	bool isMine;
	int numMinesTouching;
	int xCord;
	int yCord;
	bool isFlagged;
	bool hasBeenClicked;
};

