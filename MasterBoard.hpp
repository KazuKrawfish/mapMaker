#ifndef MASTERBOARD_HPP__
#define MASTERBOARD_HPP__

#include <vector>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <random>
#include <cmath>
#include "SFML/Graphics.hpp"

#include "Province.hpp"


class inputLayer;
//class province;
class tile;

//Max window size is the physical size of the window:
const int MAX_WINDOW_HEIGHT = 14;
const int MAX_WINDOW_WIDTH = 15;

const int numberOfCountries = 10;
const int numberOfProvinces = 20;

const int TILE_SIZE = 50;


struct country
{
	country() 
	{
		name = "UNKNOWN";
		nationalPopulation = 0;
		listOfControlledProvinces.clear();

	}
	std::string name;
	std::vector <int> listOfControlledProvinces;
	int nationalPopulation = 0;

};



class MasterBoard
{
public:
	
	int gameTurn = 0;

	MasterBoard(sf::Texture* inputTexture, sf::RenderWindow* inputWindow);
	bool checkNeighbors(int x, int y);

	//MAP GENERATION//////////////////
	int generateMap();
	int generateNames();
	int generatePrecipAndTemp();

	//Political//////////////////
	std::vector <country> listOfCountries;
	std::vector<province> listOfProvinces;
	int initializeAllPopulation();
	int initializeProvince(int input);
	//Political//////////////////

	//MAP GENERATION/////////////////

	const int BOARD_WIDTH = 30;
	const int BOARD_HEIGHT = 18;

	const int WINDOW_HEIGHT = 18;
	const int WINDOW_WIDTH = 30;

	int checkWindow();
	int clearBoard();


	std::vector<std::vector<tile>>  Board;
	
	int windowLocationX = 0;
	int windowLocationY = 0;

	//GRAPHICS	////////////////////////////////
	sf::Texture * myTexture;
	sf::Window *  myWindow;
	//GRAPHICS	///////////////////////////////


	//GAME MECHANICS//////////////////////////

	int advanceTurn();
	int updateAllProvinces();
	int updateProvince(int input);



	//GAME MECHANICS//////////////////////////

};




#endif /* MASTERBOARD_HPP__ */

