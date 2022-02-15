#ifndef TILE_H__
#define TILE_H__

#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
//#include "MasterBoard.hpp"
#include "SFML/Graphics.hpp"


//Forward declare
extern std::vector <std::vector<sf::IntRect>> rectArray;
class MasterBoard;

class tile 
{
public:
	tile() {
		symbol = '.';
	
		description = "Clear";

		controller = 0;
		province = 0;
		production = 0;
		elevation = 0;
		precipitation = 0;
		temperature = 0;
			   
		//Basic image init below
		//This is "plains"
		textureRectAnchorX = 0;
		textureRectAnchorY = 0;
		mySprite.setTextureRect(rectArray[textureRectAnchorX][textureRectAnchorY]);
		
	}

	bool checkForProperty( char terrainType)
	{
		bool isProperty = false;

		//Non property included for clarity.
		switch (terrainType)
		{
		case('.'):
		case('+'):
		case('^'):
		case('M'):
		case('='):
		case('~'):
		case('-'):
		case('*'):
			isProperty = false;
			break;
		case('A'):
		case('P'):
		case('H'):
		case('m'):
		case('n'):
		case('h'):
		case('Q'):
			isProperty = true;
			break;
		}

		return isProperty;
	}


	int determineRiverRoadType(bool thisTileChanged, MasterBoard* boardToSet);
	int determineSeaBeachType(bool thisTileChanged, MasterBoard* boardToSet);
	int production;				
	int controller = 0;			
	int province = 0;
	char symbol;
	int elevation = 0;
	int precipitation = 0;
	int temperature = 0;
	std::vector <int> provinceControlPoints;

	std::string description;
	int locationX;
	int locationY;


	//GRAPHICS ///////////////////////////
	sf::Sprite mySprite;
	sf::Sprite * animationSprite = NULL;
	sf::Texture* myTexture;
	//AnchorX and Y track the location of the "base" tile ie. neutral.
	//Only matters if sprite may change (Properties and roads/rivers)
	//Fog of war tile will always be immediately below the normal tile.
	int textureRectAnchorY;
	int textureRectAnchorX;
	//GRAPHICS ///////////////////////////

	int clearTile() {

		symbol = '.';
		description = "Clear";
		controller = 0;
		province = 0;
		
		provinceControlPoints.clear();
		
		production = 0;
		elevation = 0;
		precipitation = 0;
		temperature = 0;
		
		return 0;
	}

	int setCharacterstics(sf::Texture * inputTexture, MasterBoard* boardToSet)
	{
		myTexture = inputTexture;
		mySprite.setTexture(*myTexture);
		

		//Sprite had defualt texture-rect set in the constructor
		
		switch (symbol)
		{
		case('.'):
		{	
			description = "Clear terrain.";
		
			mySprite.setTextureRect(rectArray[0][0]);
		
			break;
		}
		case('H'):
		{
			description = "City.";
			
			production = 2000;

			textureRectAnchorX = 12;
			textureRectAnchorY = 0;

			mySprite.setTextureRect(rectArray[textureRectAnchorX + controller][textureRectAnchorY]);
			
			break;
		}
		case('m'):
		{
			description = "Mine.";
			
			production = 3000;

			break;
		}
		case('n'):
		{
			description = "Settlement.";
			
			production = 1000;

			textureRectAnchorX = 7;
			textureRectAnchorY = 0;
			
			mySprite.setTextureRect(rectArray[textureRectAnchorX + controller][textureRectAnchorY]);
			
			break;
		}
		case('h'):
		{
			description = "Factory.";
		
			production = 1000;
			textureRectAnchorX = 17;
			textureRectAnchorY = 0;

			mySprite.setTextureRect(rectArray[textureRectAnchorX + controller][textureRectAnchorY]);
			
			
			break;
		}
		case('Q'):
		{
			description = "Headquarters.";
			
			production = 1000;
			textureRectAnchorX = 22;
			textureRectAnchorY = 0;

			mySprite.setTextureRect(rectArray[textureRectAnchorX + controller][textureRectAnchorY]);
			
			break;
		}
		case('='):
		{
			description = "Road.";
			

			textureRectAnchorY = 2;
			textureRectAnchorX = 20;

			mySprite.setTextureRect(rectArray[20][2]);
			

			determineRiverRoadType(true, boardToSet);

			break;
		}
		case('^'):
		{
			description = "Hill.";
			
			mySprite.setTextureRect(rectArray[2][0]);
			
			break;
		}
		case('M'):
		{
			description = "Mountain.";
	
			mySprite.setTextureRect(rectArray[3][0]);
			
			break;
		}
		case('+'):		//Would like to have convertible to woodlot by engineer.....maybe
		{
			description = "Forest.";
			
			mySprite.setTextureRect(rectArray[1][0]);
			
			break;
		}
		case('~'):
		{
			description = "High seas.";
		

			textureRectAnchorY = 9;
			textureRectAnchorX = 0;

			mySprite.setTextureRect(rectArray[0][9]);
			
			determineSeaBeachType(true, boardToSet);

			break;
		}

		case('-'):
		{
			description = "River.";
			
			mySprite.setTextureRect(rectArray[9][2]);
			

			textureRectAnchorY = 2;
			textureRectAnchorX = 9;

			determineRiverRoadType( true, boardToSet);
			break;
		}
		case('A'):
		{
			description = "Airbase.";
			
			
			textureRectAnchorX = 32	;
			textureRectAnchorY = 0;

			mySprite.setTextureRect(rectArray[textureRectAnchorX + controller][textureRectAnchorY]);
			

			production = 1000;
			break;
		}
		case('P'):
		{
			description = "Port.";
			
			
			textureRectAnchorX = 27;
			textureRectAnchorY = 0;

			mySprite.setTextureRect(rectArray[textureRectAnchorX + controller][textureRectAnchorY]);
		

			production = 1000;
			break;
		}
		case('*'):
		{
			description = "Beach.";
			
			textureRectAnchorY = 11;
			textureRectAnchorX = 0;

			mySprite.setTextureRect(rectArray[0][11]);
			

			determineSeaBeachType(true, boardToSet);

			break;
		}
		}
		//Other terrain types go here
	
		return 0;
	}


};

#endif /* TILE_H__ */

