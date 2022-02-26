#include "Tile.hpp"
#include "MasterBoard.hpp"


int tile::determineSeaBeachType(bool thisTileChanged, MasterBoard* boardToSet)
{
	bool upNeigh = false;
	bool downNeigh = false;
	bool leftNeigh = false;
	bool rightNeigh = false;

	//Check each neighbor to see if they are same type
	//If they are, note it, and call determineSeaBeachType on that tile.
	if (locationY + 1 >= boardToSet->BOARD_HEIGHT
		|| (boardToSet->Board[locationX][locationY + 1].terrain == sea ))
	{
		downNeigh = true;
		if (locationY + 1 < boardToSet->BOARD_HEIGHT && thisTileChanged == true)
			boardToSet->Board[locationX][locationY + 1].determineSeaBeachType(false, boardToSet);
	}
	if (locationY <= 0
		|| (boardToSet->Board[locationX][locationY - 1].terrain == sea))
	{
		upNeigh = true;
		if (locationY > 0 && thisTileChanged == true)
			boardToSet->Board[locationX][locationY - 1].determineSeaBeachType(false, boardToSet);
	}
	if (locationX <= 0
		|| (boardToSet->Board[locationX - 1][locationY ].terrain == sea ))
	{
		leftNeigh = true;
		if (locationX > 0 && thisTileChanged == true)
			boardToSet->Board[locationX - 1][locationY].determineSeaBeachType(false, boardToSet);
	}
	if (locationX + 1 >= boardToSet->BOARD_WIDTH
		|| (boardToSet->Board[locationX + 1][locationY].terrain == sea ))
	{
		rightNeigh = true;
		if (locationX + 1 < boardToSet->BOARD_WIDTH && thisTileChanged == true)
			boardToSet->Board[locationX + 1][locationY].determineSeaBeachType(false, boardToSet);
	}

	
	//Change sprite rect based on selections above
	//Default is up-down
	//Sideways13 
	if (downNeigh == false && upNeigh == false && (leftNeigh == true || rightNeigh == true))
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 13][textureRectAnchorY]);
		 

	}

	//Up-down14
	if (downNeigh == true && upNeigh == true && leftNeigh == false && rightNeigh == false)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 14][textureRectAnchorY]);
		 

	}

	//Four way
	if (downNeigh == true && upNeigh == true && leftNeigh == true && rightNeigh == true)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 15][textureRectAnchorY]);
		 

	}

	//Pond
	if (downNeigh == false && upNeigh == false && leftNeigh == false && rightNeigh == false)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 8][textureRectAnchorY]);
		 

	}

	//3 Way
	if (downNeigh == true && upNeigh == true && leftNeigh == true && rightNeigh == false)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 1][textureRectAnchorY]);
		 

	}
	if (downNeigh == false && upNeigh == true && leftNeigh == true && rightNeigh == true)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 2][textureRectAnchorY]);
		 

	}
	if (downNeigh == true && upNeigh == true && leftNeigh == false && rightNeigh == true)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 3][textureRectAnchorY]);
		 

	}
	if (downNeigh == true && upNeigh == false && leftNeigh == true && rightNeigh == true)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX ][textureRectAnchorY]);
		 

	}

	//Diagonals
	if (downNeigh == false && upNeigh == true && leftNeigh == false && rightNeigh == true)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 6][textureRectAnchorY]);
		 

	}
	if (downNeigh == true && upNeigh == false && leftNeigh == false && rightNeigh == true)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 7][textureRectAnchorY]);
		 

	}
	if (downNeigh == true && upNeigh == false && leftNeigh == true && rightNeigh == false)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 4][textureRectAnchorY]);
		 

	}
	if (downNeigh == false && upNeigh == true && leftNeigh == true && rightNeigh == false)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 5][textureRectAnchorY]);
		 

	}

	//Bays
	if (downNeigh == false && upNeigh == false && leftNeigh == false && rightNeigh == true)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 11][textureRectAnchorY]);
		 

	}
	if (downNeigh == true && upNeigh == false && leftNeigh == false && rightNeigh == false)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 12][textureRectAnchorY]);
		 

	}
	if (downNeigh == false && upNeigh == false && leftNeigh == true && rightNeigh == false)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 9][textureRectAnchorY]);
		 

	}
	if (downNeigh == false && upNeigh == true && leftNeigh == false && rightNeigh == false)
	{
		mySprite.setTextureRect(rectArray[textureRectAnchorX + 10][textureRectAnchorY]);
		 

	}


	return 0;

}
