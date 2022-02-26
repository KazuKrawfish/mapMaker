#ifndef TILE_H__
#define TILE_H__

#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"

extern std::vector <std::vector<sf::IntRect>> rectArray;
class MasterBoard;

//climateType matrix:						//Wet				Medium			Dry				Hills				Mntns
enum climateType			/*Freezing*/	{Ice,				Taiga,			Tundra,			ArcticHighland,		ArcticMountain,
							/*Cool*/		ConiferousForest,	Grassland,		Steppe,			WoodedHighland,		WoodedMountain,
							/*Warm*/		DeciduousForest,	Scrubland,		Mediterranean,	Highland,			Mountain,
							/*Hot*/			Jungle,				Savanna,		Desert,			HighDesert,			DesertMountain, 
																								JungleHighland,		JungleMountain		
};

//Precipitation, temperature, terrain array used for initialization of tiles
const climateType climateChoices[3][4][3] =
{	 //Cold 								cool 											warm 											hot {plain,hill,mtn}
  { {Ice,ArcticHighland,ArcticMountain}, {ConiferousForest,WoodedHighland,WoodedMountain}, {DeciduousForest,WoodedHighland,WoodedMountain}, {Jungle,JungleHighland,JungleMountain} }, // Wet
  { {Taiga,ArcticHighland,ArcticMountain}, {Grassland,WoodedHighland,WoodedMountain}, {Scrubland,WoodedHighland,WoodedMountain}, {Savanna,JungleHighland,JungleMountain} },//Normal
  { {Tundra,ArcticHighland,ArcticMountain}, {Steppe,Highland,Mountain}, {Mediterranean,Highland,Mountain}, {Desert,HighDesert,DesertMountain} }	//Dry	
};

enum terrainType {sea, land};

class tile 
{
public:
	int determineSeaBeachType(bool thisTileChanged, MasterBoard* boardToSet);
	
	//Basic Characteristics////////////////
	int controller = 0;			
	int province = 0;
	int elevation = 0;
	int precipitation = 0;
	int temperature = 0;
	double agriProductivity = 0;
	climateType climate = Steppe;
	terrainType terrain = land;
	std::vector <int> provinceControlPoints;
	std::string description;
	int locationX;
	int locationY;
	//Basic Characteristics////////////////


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

	tile() {

		climate = Steppe;
		terrain = land;

		description = "Clear";

		controller = 0;
		province = 0;

		elevation = 0;
		precipitation = 0;
		temperature = 0;
		agriProductivity = 0;

		//Basic image init below
		//This is "plains"
		textureRectAnchorX = 0;
		textureRectAnchorY = 0;
		mySprite.setTextureRect(rectArray[textureRectAnchorX][textureRectAnchorY]);

	}

	int clearTile() {

		terrain = land;
		climate = Steppe;
		description = "Clear";
		controller = 0;
		province = 0;
		
		provinceControlPoints.clear();
		

		elevation = 0;
		precipitation = 0;
		temperature = 0;
		agriProductivity = 0;
		
		return 0;
	}
	

	//Initializes tile based on precipitation, elevation, and temperature.
	//Thus it requires these to be set previously by Masterboard.
	int setCharacterstics(sf::Texture* inputTexture, MasterBoard* boardToSet)
	{
		myTexture = inputTexture;
		mySprite.setTexture(*myTexture);

		int temperatureChoice = 0;
		int precipitationChoice = 0;
		int elevationChoice = 0;

		//First categorize different characteristics to use in the choices array.
		//Precip. choices
		if (precipitation < -20)		//Dry
		{
			precipitationChoice = 2;
		}
		else
			if (precipitation >= -10 && precipitation < 40)	//Medium
			{
				precipitationChoice = 1;
			}
			else //Wet
			{
				precipitationChoice = 0;
			}

		//Temperature choices
		if (temperature < -20) //Freezing
		{
			temperatureChoice = 0;
		}
		else
			if (temperature >= -20 && temperature < 10)	//Cool
			{
				temperatureChoice = 1;
			}
			else
				if (temperature >= 10 && temperature < 50)	//Warm
				{
					temperatureChoice = 2;

				}
				else				//Hot
				{
					temperatureChoice = 3;
				}

		//Elevation choices
		if (elevation < 40)
		{
			elevationChoice = 0;
		}
		else
			if (elevation < 80)
			{
				elevationChoice = 1;
			}
			else elevationChoice = 2;


		//Now assign characteristics to tile based on terrain and climate
		//If it's sea then nothing else matters.
		if (terrain == sea)
		{

			description = "High seas.";

			textureRectAnchorY = 9;
			textureRectAnchorX = 0;
			mySprite.setTextureRect(rectArray[0][9]);
			determineSeaBeachType(true, boardToSet);

		}
		else		//If not sea, consult chart
		{			
			climate = climateChoices[precipitationChoice][temperatureChoice][elevationChoice];
		

		//Now with a climate type, other characteristics can be added.
		switch (climate)
		{
		case(Ice):
		{
			description = "Ice";
			mySprite.setTextureRect(rectArray[1][3]);
			agriProductivity = 5;
			break;
		}
		case(Tundra):
		{
			description = "Tundra";
			mySprite.setTextureRect(rectArray[0][3]);
			agriProductivity = 10;
			break;
		}
		case(Taiga):
		{
			description = "Taiga";
			mySprite.setTextureRect(rectArray[2][3]);
			agriProductivity = 15;
			break;
		}
		case(ConiferousForest):
		{
			description = "Coniferous Forest";
			mySprite.setTextureRect(rectArray[1][2]);
			agriProductivity = 100;
			break;
		}
		case(Scrubland):
		{
			description = "Scrubland";
			mySprite.setTextureRect(rectArray[1][1]);
			agriProductivity = 120;
			break;
		}
		case(Mediterranean):
		{
			description = "Mediterranean Plain";
			mySprite.setTextureRect(rectArray[1][0]);
			agriProductivity = 100;

			break;
		}
		case(DeciduousForest):
		{
			description = "Deciduous Forest";
			mySprite.setTextureRect(rectArray[2][2]);
			agriProductivity = 150;
			break;
		}
		case(Grassland):
		{
			description = "Grassland";
			mySprite.setTextureRect(rectArray[2][1]);
			agriProductivity = 100;
			break;
		}
		case(Steppe):
		{
			description = "Steppe";
			mySprite.setTextureRect(rectArray[2][0]);
			agriProductivity = 80;

			break;
		}
		case(Desert):
		{
			description = "Desert";
			mySprite.setTextureRect(rectArray[0][0]);
			agriProductivity = 10;
			break;
		}
		case(Savanna):
		{
			description = "Savvana";
			mySprite.setTextureRect(rectArray[0][1]);
			agriProductivity = 120;
			break;
		}
		case(Jungle):
		{
			description = "Jungle";
			mySprite.setTextureRect(rectArray[0][2]);
			agriProductivity = 80;

			break;
		}
		case(ArcticHighland):
		{
			description = "Alpine Highland";
			mySprite.setTextureRect(rectArray[3][3]);
			agriProductivity = 5;

			break;
		}
		case(ArcticMountain):
		{
			description = "Alpine Mountain";
			mySprite.setTextureRect(rectArray[4][3]);
			agriProductivity = 5;

			break;
		}
		case(WoodedHighland):
		{
			description = "Wooded Highland";
			mySprite.setTextureRect(rectArray[5][1]);
			agriProductivity = 80;

			break;
		}
		case(WoodedMountain):
		{
			description = "WoodedMountain";
			mySprite.setTextureRect(rectArray[6][1]);
			agriProductivity = 60;

			break;
		}
		case(Highland):
		{
			description = "Highland";
			mySprite.setTextureRect(rectArray[5][0]);
			agriProductivity = 50;

			break;
		}
		case(Mountain):
		{
			description = "Mountain";
			mySprite.setTextureRect(rectArray[6][0]);
			agriProductivity = 40;

			break;
		}
		case(JungleHighland):
		{
			description = "Jungle Highland";
			mySprite.setTextureRect(rectArray[3][1]);
			agriProductivity = 50;

			break;
		}
		case(JungleMountain):
		{
			description = "Jungle Mountain";
			mySprite.setTextureRect(rectArray[4][1]);
			agriProductivity = 40;

			break;
		}
		case(HighDesert):
		{
			description = "High Desert";
			mySprite.setTextureRect(rectArray[3][0]);
			agriProductivity = 20;

			break;
		}
		case(DesertMountain):
		{
			description = "Desert Mountain";
			mySprite.setTextureRect(rectArray[4][0]);
			agriProductivity = 5;

			break;
		}

		}

	}

		return 0;
	}
};

#endif /* TILE_H__ */

