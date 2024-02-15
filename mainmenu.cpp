#include "inputLayer.hpp"
#include "mainmenu.h"
#include <iostream>
#include <ctype.h>
#include <fstream>
#include <stdio.h>
#include <filesystem>
#include "MasterBoard.hpp"

mainMenu::mainMenu(sf::RenderWindow* myWindow, sf::Texture* gameTexture , sf::Font* cour)
{
	myTexture = gameTexture;
	myFont = cour;
	mywindow = myWindow;

	logStream.open(logFileName, std::ofstream::app);

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

	boardToPlay->initializeAllProvinces();


	sf::Event playerInput;
	while (true)
	{
		// while there are pending events...
		while (mywindow->pollEvent(playerInput))
		{
			if(InputLayer->screen == gameBoardScreen)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{

					boardToPlay->clearBoard();

					boardToPlay->generateMap();

					setCharacteristics(boardToPlay);

					boardToPlay->initializeAllProvinces();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{

					InputLayer->screen = worldDataScreen;

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{

					//boardToPlay->saveGame();
					std::cout << "This currently doesn't do anything!!!!" << std::endl;

				}
				if(playerInput.type ==  playerInput.KeyReleased && playerInput.key.code == sf::Keyboard::N)
				{

					boardToPlay->advanceTurn();

				}
				//If left mouse click
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					//select province and provide data screen
					InputLayer->selectedProvince = boardToPlay->selectProvince();
					
					if (InputLayer->selectedProvince != 0)
						InputLayer->screen = provinceDataScreen;
					else  InputLayer->screen = gameBoardScreen;
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					if (InputLayer->screen == gameBoardScreen)
					{
						boardToPlay->checkWindow();
					}
						
				}
			}
			else if (InputLayer->screen == provinceDataScreen || InputLayer->screen == worldDataScreen)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					//Deselect province
					InputLayer->selectedProvince = 0;
					InputLayer->screen = gameBoardScreen;
				}


			}


			InputLayer->printScreen(boardToPlay, false);

		}

	}


	return 0;
}