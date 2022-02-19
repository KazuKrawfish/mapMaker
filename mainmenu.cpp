#include "MasterBoard.hpp"
#include "inputLayer.hpp"
#include "mainmenu.h"
#include <iostream>
#include <ctype.h>
#include <fstream>
#include <stdio.h>
#include <filesystem>

mainMenu::mainMenu(sf::RenderWindow* myWindow, sf::Texture* gameTexture, sf::Font* cour, 
	sf::Texture* inputMenuWallpaper, sf::Texture* inputStartWallPaper, sf::Texture* inputTopMenu,
	sf::Texture* inputstartScreenStatement, sf::Music* inputIntroMusic)
{
	myTexture = gameTexture;
	menuWallPaper = inputMenuWallpaper;
	startWallPaper = inputStartWallPaper;
	topMenuTexture = inputTopMenu;
	startScreenStatement = inputstartScreenStatement;
	introMusic = inputIntroMusic;
	myFont = cour;
	mywindow = myWindow;
	
	
	//Initialize the clearField sprite used for player string input

}

int mainMenu::setCharacteristics(MasterBoard* LoadBoard)
{
	for (int x = 0; x < LoadBoard->BOARD_WIDTH; x++)
	{
		for (int y = 0; y < LoadBoard->BOARD_HEIGHT; y++)
		{
			LoadBoard->Board[x][y].locationX = x;
			LoadBoard->Board[x][y].locationY = y;


		}
	}

	for (int x = 0; x < LoadBoard->BOARD_WIDTH; x++)
	{
		for (int y = 0; y < LoadBoard->BOARD_HEIGHT; y++)
		{
			LoadBoard->Board[x][y].setCharacterstics(myTexture, LoadBoard);
		}
	}


	return 0;
}

int mainMenu::playGame(MasterBoard* boardToPlay, inputLayer* InputLayer)
{
	boardToPlay->generateMap();
	
	setCharacteristics(boardToPlay);


	sf::Event playerInput;
	while (true)
	{
		// while there are pending events...
		while (mywindow->pollEvent(playerInput))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				
				boardToPlay->clearBoard();

				boardToPlay->generateMap();

				setCharacteristics(boardToPlay);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
			{
		
				InputLayer->viewStatus = defaultView;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
		
				InputLayer->viewStatus = politicalView;
		
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			{

				InputLayer->viewStatus = temperatureView;

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{

				InputLayer->viewStatus = precipitationView;

			}

			boardToPlay->checkWindow();

			InputLayer->printScreen(boardToPlay, false);

		}

	}


	return 0;
}