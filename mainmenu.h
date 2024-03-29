#ifndef MAINMENU_HPP__
#define MAINMENU_HPP__

#include "Tile.hpp"
#include <SFML/Audio.hpp>
#include <fstream>

class inputLayer;
class MasterBoard;


class mainMenu
{
public:

	//gameTurn represents the overall turn, which increments once everyone has cycled through one player turn.
	int gameTurn = 1;

	bool veryFirstTurn = true;
	bool isItSaveGame = false;
	bool debugMode = false;

	std::string myPlayerName = "~";
	int setCharacteristics(MasterBoard* LoadBoard);
	int playGame(MasterBoard* boardToPlay, inputLayer* InputLayer);
	

	
	//CONSTRUCTOR
	mainMenu(sf::RenderWindow* myWindow, sf::Texture* gameTexture, sf::Font* cour);
	//CONSTRUCTOR

	const int menuTextSize = 20;

	//Main Menu Interface ///////////////////////
	int menuIterator = 0;
	std::vector <std::string> topMenuOptions{ "Load Game","New Game","Join Remote Game","Editor Mode"};
	//Main Menu Interface ///////////////////////



	//SFML Objects		/////////////////////////
	sf::RenderWindow* mywindow;
	sf::Texture* myTexture;
	sf::Font* myFont;

	sf::Music* introMusic;
	//SFML Objects end	/////////////////////////

	std::ofstream logStream;
	std::string logFileName = "history.log";


};

#endif /* MAINMENU_HPP__ */
