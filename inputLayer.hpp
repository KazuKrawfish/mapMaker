#ifndef INPUT_HPP__
#define INPUT_HPP__

#include <SFML/Audio.hpp>
//#include "MasterBoard.hpp"
#include "mainmenu.h"
#include "Tile.hpp"

class MasterBoard;

enum gameInputLayer { defaultView, politicalView, temperatureView, precipitationView};
enum specialKey {showMinions, hideMinions};
enum colorCode {
	unused, fogLandTile, waterTile, fogWaterTile, player1Minion,
	player2Minion, player3Minion, player4Minion, player5Minion, player6Minion,
	player1Tile, player2Tile, player3Tile, player4Tile, player5Tile, player6Tile,
	fogPlayer1Tile, fogPlayer2Tile, fogPlayer3Tile, fogPlayer4Tile,
	fogPlayer5Tile, fogPlayer6Tile, neutralTile, fogNeutralTile, landTile, cursorSymbol,
	attackRangeSymbol, moveRangeSymbol, player1MinionInverse, player2MinionInverse,
	player3MinionInverse, player4MinionInverse, player5MinionInverse, player6MinionInverse
};


class inputLayer
{
public:

	inputLayer(mainMenu* inputMainMenu, sf::RenderWindow* myWindow, sf::Texture* gameTexture, sf::Font* cour, std::vector <sf::Sound>* inputSoundEffects );
	

	//Print Whole Screen
	int printStatus(MasterBoard* boardToPrint);
	int printLowerScreen(MasterBoard* boardToPrint);
	int printUpperScreen(MasterBoard* boardToPrint, bool withinAnimation);
	int printScreen(MasterBoard* boardToPrint, bool withinAnimation);
	int printSingleTile(int screenX, int screenY, int actualX, int actualY, MasterBoard* boardToPrint, bool withinAnimation);

	std::string eventText = "";

	gameInputLayer viewStatus = defaultView;
	mainMenu* MainMenu;

	//MenuCrawlerObjects /////////////////////////
	int menuCursor = 0;
	std::vector <std::string> menuOptions { "End Turn","Save Game","Main Menu","Load Game","Restart Map","Return to Game"	};
	std::vector <std::string> factoryOptions{ "Infantry\t1000", "Specialist\t3000", "Cavalry\t4000","APC\t5000","Artillery\t6000", "Armor\t7000",
												"Anti-Aircraft\t8000", "Rocket Artillery\t15000", "Heavy Armor\t16000" };
	std::vector <std::string> airbaseOptions{ "Transport Copter\t5000", "Attack Copter\t9000", "Interceptor\t15000", "Bomber\t18000"};
	std::vector <std::string> portOptions{ "Gunboat\t6000", "Cruiser\t14000", "Landing Ship\t12000", "Submarine\t18000", "Battleship\t25000", "Aircraft Carrier\t25000" };
	//MenuCrawlerObjects /////////////////////////

	//SFML Objects		/////////////////////////
	std::vector <sf::Sound> * soundEffects;
	bool soundsOn = false;
	int speedFactor = 5;		//1 is normal. 10 is ultra fast.
	sf::Texture* inputLayerTexture;
	sf::Font* inputLayerFont;
	sf::RenderWindow* inputLayerWindow;
	int menuLineTracker = 0;
	std::vector <sf::Color> politicalColors;
	std::vector <sf::Color> temperatureColors;
	//SFML Objects end	/////////////////////////


private:

};


#endif /* INPUT_HPP__ */


