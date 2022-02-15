#ifndef MAINMENU_HPP__
#define MAINMENU_HPP__

#include "Tile.hpp"
#include "MasterBoard.hpp"
#include <SFML/Audio.hpp>

class inputLayer;
class MasterBoard;

enum mainMenuStatus { topmenu,  playingMap, waitingForRemotePlayer };
enum interactionMethod {unchosen, localSkirmish, localCampaign, remote};


class mainMenu
{
public:

	//gameTurn represents the overall turn, which increments once everyone has cycled through one player turn.
	int gameTurn = 1;
	//Initialized to false because only if we select join is this true, and that will be dealt with in that function..
	bool awaitingFirstTurnThisSession = false;
	//skipOneInput indicates that we skip on player input, in order to print the next screen. (Back to main menu, etc.)
	bool skipOneInput = false;
	//interactionMethod refers to whether this will be remote or local game.
	interactionMethod gameType = unchosen;
	//mainMenuStatus will indicate what interace the player is interacting with.
	mainMenuStatus menuStatus = topmenu;
	bool veryFirstTurn = true;
	bool isItSaveGame = false;
	bool debugMode = false;
	std::string sessionName = "localsession";
	std::string myPlayerName = "~";
	int setCharacteristics(MasterBoard* LoadBoard);
	int playGame(MasterBoard* boardToPlay, inputLayer* InputLayer);
	

	
	//CONSTRUCTOR
	mainMenu(sf::RenderWindow* myWindow, sf::Texture* gameTexture, sf::Font* cour, 
		sf::Texture* inputMenuWallpaper, sf::Texture* inputStartWallPaper, sf::Texture* inputTopMenu ,
		sf::Texture* inputstartScreenStatement, sf::Music* inputIntroMusic);
	//CONSTRUCTOR

	const int menuTextSize = 20;
	std::string nextMissionName, missionBriefing;
	int briefingLineNumber = 0;

	//Main Menu Interface ///////////////////////
	int menuIterator = 0;
	std::vector <std::string> topMenuOptions{ "Load Game","New Game","Join Remote Game","Editor Mode"};
	//Main Menu Interface ///////////////////////



	//SFML Objects		/////////////////////////
	sf::RenderWindow* mywindow;
	sf::Texture* myTexture;
	sf::Texture* menuWallPaper;
	sf::Texture* startWallPaper;
	sf::Texture* startScreenStatement;
	sf::Texture* topMenuTexture;
	sf::Font* myFont;

	sf::Music* introMusic;
	//SFML Objects end	/////////////////////////


};

#endif /* MAINMENU_HPP__ */
