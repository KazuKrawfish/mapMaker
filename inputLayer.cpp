
#include "inputLayer.hpp"
#include "mainmenu.h"
#include <iostream>
#include <ctype.h>
#include <fstream>
#include <cmath>
#include <thread>


inputLayer::inputLayer(mainMenu* inputMainMenu, sf::RenderWindow* myWindow, sf::Texture* gameTexture, sf::Font* cour, std::vector <sf::Sound>* inputSoundEffects)
{
	inputLayerTexture = gameTexture;
	inputLayerFont = cour;
	inputLayerWindow = myWindow;
	MainMenu = inputMainMenu;
	soundEffects = inputSoundEffects;


	politicalColors.resize(numberOfCountries + 1);
	temperatureColors.resize(4);
	precipColors.resize(4);

	temperatureColors[0] = sf::Color::Cyan;
	temperatureColors[1] = sf::Color::Yellow;
	temperatureColors[2].r = 250;	//Orange
	temperatureColors[2].g = 150;
	temperatureColors[3] = sf::Color::Red;

	precipColors[0] = sf::Color::Yellow;
	precipColors[1] = sf::Color::Green;
	precipColors[2] = sf::Color::Cyan;
	precipColors[3] = sf::Color::Blue;

	politicalColors[1] = sf::Color::Red;
	politicalColors[2] = sf::Color::Green;
	politicalColors[3] = sf::Color::Blue;
	politicalColors[4] = sf::Color::Yellow;
	politicalColors[5] = sf::Color::Magenta;
	politicalColors[6] = sf::Color::Cyan;

	if (numberOfCountries > 6) {
		for (int i = 7; i < numberOfCountries + 1; i++)
		{
			int prim = rand() % 3;

			if (prim == 0)
			{
				politicalColors[i].r = 50 + i * 10;

			}
			if (prim == 1)
			{
				politicalColors[i].b = 50 + i * 10;
			}
			if (prim == 2)
			{
				politicalColors[i].g = 50 + i * 10;
			}

		}
	}
	//Increase transparency for political colors so we can highlight tiles
	for (int i = 1; i < numberOfCountries + 1; i++) 
	{
		politicalColors[i].a = 160;
	}

}

int inputLayer::printSingleTile(int screenX, int screenY, int actualX, int actualY, MasterBoard* boardToPrint, bool withinAnimation)
{
	tile* tileToPrint = &boardToPrint->Board[actualX][actualY];

	//First print tile.
	//Change color of tile if political view is on.
	if (viewStatus == politicalView && tileToPrint->controller != 0)
	{
		//Use local sprite to avoid changing the actual sprite's color.
		
		//First print a very faint image of the terrain
		//Must have lower alpha for transparency
		sf::Sprite politicalColorSprite = tileToPrint->mySprite;
		sf::Color transparentColor;
		transparentColor = politicalColorSprite.getColor();
		transparentColor.a = 100;				
		politicalColorSprite.setColor(transparentColor);
		inputLayerWindow->draw(politicalColorSprite);

		//Then print color over it
		politicalColorSprite = tileToPrint->mySprite;
		politicalColorSprite.setTextureRect(rectArray[5][0]);
		politicalColorSprite.setPosition(screenX * TILE_SIZE, screenY * TILE_SIZE);
		politicalColorSprite.setColor(politicalColors[tileToPrint->controller]);
		inputLayerWindow->draw(politicalColorSprite);
		
	}
	else //If temperatureView is on, print special blank tile with that color assigned.
		if (viewStatus == temperatureView) 
		{
			//Use local sprite to avoid changing the actual sprite's color.
			sf::Sprite temperatureColorSprite = tileToPrint->mySprite;
			temperatureColorSprite.setTextureRect(rectArray[5][0]);
			temperatureColorSprite.setPosition(screenX * TILE_SIZE, screenY * TILE_SIZE);
			int tempColor = 0;
			if (tileToPrint->temperature < -20)
				tempColor = 0;
			else if (tileToPrint->temperature < 10)
				tempColor = 1;
			else if (tileToPrint->temperature < 51)
				tempColor = 2;
			else
				tempColor = 3;
			temperatureColorSprite.setColor(temperatureColors[tempColor]);
			inputLayerWindow->draw(temperatureColorSprite);
		}
		else
		if (viewStatus == precipitationView)
		{
			//Use local sprite to avoid changing the actual sprite's color.
			sf::Sprite precipColorSprite = tileToPrint->mySprite;
			precipColorSprite.setTextureRect(rectArray[5][0]);
			precipColorSprite.setPosition(screenX * TILE_SIZE, screenY * TILE_SIZE);
			int precipColor = 0;
			if (tileToPrint->precipitation < -20)
				precipColor = 0;
			else if (tileToPrint->precipitation < 10)
				precipColor = 1;
			else if (tileToPrint->precipitation < 51)
				precipColor = 2;
			else
				precipColor = 3;
			precipColorSprite.setColor(precipColors[precipColor]);
			inputLayerWindow->draw(precipColorSprite);
		}
		else	//If default view, print the normal sprite.
		{	
			tileToPrint->mySprite.setPosition(screenX * TILE_SIZE, screenY * TILE_SIZE);
			inputLayerWindow->draw(tileToPrint->mySprite);
		}

	//Now handle river tiles onto sea and beach
	if (tileToPrint->symbol == '~' || tileToPrint->symbol == '*') 
	{
		sf::Sprite riverSprite;
		riverSprite.setTexture(*inputLayerTexture);
		riverSprite.setPosition(screenX * TILE_SIZE, screenY * TILE_SIZE);

		int riverYCoord = 9;

		if (actualX < boardToPrint->BOARD_WIDTH - 1 &&  boardToPrint->Board[actualX+1][actualY].symbol == '-') 
		{
			riverSprite.setTextureRect(rectArray[16][riverYCoord]);
			inputLayerWindow->draw(riverSprite);
		}
		if (actualY < boardToPrint->BOARD_HEIGHT - 1 && boardToPrint->Board[actualX ][actualY+1].symbol == '-')
		{
			riverSprite.setTextureRect(rectArray[18][riverYCoord]);
 			inputLayerWindow->draw(riverSprite);
		}
		if (actualY > 0 && boardToPrint->Board[actualX][actualY - 1].symbol == '-')
		{
			riverSprite.setTextureRect(rectArray[19][riverYCoord]);
			inputLayerWindow->draw(riverSprite);
		}
		if (actualX > 0 && boardToPrint->Board[actualX - 1][actualY].symbol == '-')
		{
			riverSprite.setTextureRect(rectArray[17][riverYCoord]);
			inputLayerWindow->draw(riverSprite);
		}
	}

	//Now handle shoal onto sea
	if (tileToPrint->symbol == '~')
	{
		sf::Sprite beachSprite;
		beachSprite.setTexture(*inputLayerTexture);
		beachSprite.setPosition(screenX * TILE_SIZE, screenY * TILE_SIZE);

		int beachYCoord = 11;

		if (actualX < boardToPrint->BOARD_WIDTH - 1 && boardToPrint->Board[actualX + 1][actualY].symbol == '*')
		{
			beachSprite.setTextureRect(rectArray[16][beachYCoord]);
			inputLayerWindow->draw(beachSprite);
		}
		if (actualY < boardToPrint->BOARD_HEIGHT - 1 && boardToPrint->Board[actualX][actualY + 1].symbol == '*')
		{
			beachSprite.setTextureRect(rectArray[18][beachYCoord]);
			inputLayerWindow->draw(beachSprite);
		}
		if (actualY > 0 && boardToPrint->Board[actualX][actualY - 1].symbol == '*')
		{
			beachSprite.setTextureRect(rectArray[19][beachYCoord]);
			inputLayerWindow->draw(beachSprite);
		}
		if (actualX > 0 && boardToPrint->Board[actualX - 1][actualY].symbol == '*')
		{
			beachSprite.setTextureRect(rectArray[17][beachYCoord]);
			inputLayerWindow->draw(beachSprite);
		}
	}
	   	
	//If controlled by a country draw any borders with other countries
	if (viewStatus == defaultView && tileToPrint->symbol != '~' && tileToPrint->controller != 0) 
	{
		sf::Sprite borderSprite;
		borderSprite.setTexture(*inputLayerTexture);
		borderSprite.setPosition(screenX * TILE_SIZE, screenY * TILE_SIZE);

		borderSprite.setColor(politicalColors[tileToPrint->controller]);

		//If not at right edge check right neighbor
		if (actualX < boardToPrint->BOARD_WIDTH - 1/* && boardToPrint->Board[actualX + 1][actualY].controller != 0 */
			&& boardToPrint->Board[actualX + 1][actualY].controller != tileToPrint->controller)
		{
			//Draw  border if neighbor is non-neutral and not friendly
			borderSprite.setTextureRect(rectArray[27][4]);
			inputLayerWindow->draw(borderSprite);
			
		}
		//If not at bottom edge check below neighbor
		if (actualY < boardToPrint->BOARD_HEIGHT - 1 /*&& boardToPrint->Board[actualX ][actualY + 1].controller != 0*/
			&& boardToPrint->Board[actualX ][actualY + 1].controller != tileToPrint->controller)
		{
			borderSprite.setTextureRect(rectArray[26][4]);
			inputLayerWindow->draw(borderSprite);

		}
		//If not at left edge check left neighbor
		if (actualX > 0 /*&& boardToPrint->Board[actualX- 1][actualY ].controller != 0*/
			&& boardToPrint->Board[actualX- 1][actualY].controller != tileToPrint->controller)
		{
			borderSprite.setTextureRect(rectArray[24][4]);

			inputLayerWindow->draw(borderSprite);

		}
		//If not at top edge check top neighbor
		if (actualY > 0 /*&& boardToPrint->Board[actualX ][actualY - 1].controller != 0 */
			&& boardToPrint->Board[actualX ][actualY - 1].controller != tileToPrint->controller)
		{
			borderSprite.setTextureRect(rectArray[25][4]);
			inputLayerWindow->draw(borderSprite);

		}
	}
	
	if (tileToPrint->animationSprite != NULL)
	{
		//If there is some additional animation, print that too, on top of everything else
		//It must be set by previous function
		tileToPrint->animationSprite->setPosition(screenX * TILE_SIZE, screenY * TILE_SIZE);
		inputLayerWindow->draw(*(tileToPrint->animationSprite));
	}

	return 1;
}

int inputLayer::printStatus(MasterBoard* boardToPrint)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*inputLayerWindow);

	if (mousePosition.x > 0 && mousePosition.y > 0 && mousePosition.x < boardToPrint->WINDOW_WIDTH * TILE_SIZE && mousePosition.y < boardToPrint->WINDOW_HEIGHT * TILE_SIZE)
	{
		//Description and Owner///////
		int myController = boardToPrint->Board[mousePosition.x / TILE_SIZE][mousePosition.y / TILE_SIZE].controller;
		int myProvince = boardToPrint->Board[mousePosition.x / TILE_SIZE][mousePosition.y / TILE_SIZE].province;
				
		std::string myControllerName = "Neutral";		
		
		if (myController != 0)
			myControllerName = boardToPrint->listOfCountries[myController].name;
		
		std::string nameOfProvince = "";
		if (myProvince != 0)
			nameOfProvince = boardToPrint->listOfProvinces[myProvince].name;

		char buffer[100];
		snprintf(buffer, 100, "%s Province(%d)\nController: %s(%d)", nameOfProvince.c_str(), myProvince, myControllerName.c_str(), myController);
		std::string tileDescription = buffer;
		//Description and Owner//////

		//ELEVATION//////////////////
		int elevation = boardToPrint->Board[mousePosition.x / TILE_SIZE][mousePosition.y / TILE_SIZE].elevation;
		snprintf(buffer,100, "\nElevation: %d", elevation);
		///	tileDescription += '\n';
		//tileDescription += "Elevation: ";
		tileDescription += buffer;
		//ELEVATION//////////////////

		//Precip/Temp////////////////
		int precip = boardToPrint->Board[mousePosition.x / TILE_SIZE][mousePosition.y / TILE_SIZE].precipitation;
		int temp = boardToPrint->Board[mousePosition.x / TILE_SIZE][mousePosition.y / TILE_SIZE].temperature;
		snprintf(buffer, 100, "\nTemperature: %d\nPrecipitation: %d\n", temp, precip);
		tileDescription += buffer;
		//Precip/Temp////////////////
			
		sf::Text newText(tileDescription, *inputLayerFont, MainMenu->menuTextSize);

		newText.setPosition(boardToPrint->WINDOW_WIDTH * 52, menuLineTracker * MainMenu->menuTextSize + 4);
		inputLayerWindow->draw(newText);
	}
	return 0;
}

int inputLayer::printLowerScreen(MasterBoard* boardToPrint) {
	

		printStatus(boardToPrint);

	return 0;

}

int inputLayer::printUpperScreen(MasterBoard* boardToPrint, bool withinAnimation) {
	//windowLocation is a single scalar representing x and y.
	//We do some basic math to break it into the two values for the function.
	//Need to convert windowLocation into a better two part variable.
	int windowY = boardToPrint->windowLocationY;
	int windowX = boardToPrint->windowLocationX;
	
	//Go through the whole "board", staying within the bounds of window's x and y coordinates.
	for (int i = windowY; i < (windowY + boardToPrint->WINDOW_HEIGHT); i++)
	{
		for (int j = windowX; j < (windowX + boardToPrint->WINDOW_WIDTH); j++)
		{
			printSingleTile((j - windowX),  (i - windowY), j , i , boardToPrint, withinAnimation);
		
		}
		
	}

	return 0;
}

int inputLayer::printScreen(MasterBoard* boardToPrint, bool withinAnimation)
{

	inputLayerWindow->clear();
	printUpperScreen(boardToPrint, withinAnimation);
	printLowerScreen(boardToPrint);
	inputLayerWindow->display();
	

	
	//Reset line tracker after each print.
	menuLineTracker = 0;
	
	return 0;
}