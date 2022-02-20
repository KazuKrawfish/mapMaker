#ifndef MASTERBOARD_HPP__
#define MASTERBOARD_HPP__

#include "Tile.hpp"
#include "mainmenu.h"
#include <vector>

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <random>
#include <cmath>

class inputLayer;

//Max window size is the physical size of the window:
const int MAX_WINDOW_HEIGHT = 14;
const int MAX_WINDOW_WIDTH = 16;

const int numberOfCountries = 10;
const int numberOfProvinces = 20;

const int TILE_SIZE = 50;

struct xyCoord 
{
	xyCoord(int inputX, int inputY)
	{
		 XCoord = inputX;
		 YCoord = inputY;

	}

	int XCoord = 0;
	int YCoord = 0;
};

struct province 
{
	province()
	{
		numberOfSquares = 0;
		Population = 0;
		name = "UNKNOWN";
		controller = 0;
		listOfTiles.clear();
	}

	int numberOfSquares = 0;
	double Population = 0;
	std::string name;
	int controller = 0;
	std::vector <xyCoord> listOfTiles;
	
};

struct country
{
	country() 
	{
		name = "UNKNOWN";
		listOfControlledProvinces.clear();

	}
	std::string name;
	std::vector <int> listOfControlledProvinces;

};



class MasterBoard
{
public:
	
	MasterBoard(sf::Texture* inputTexture, sf::RenderWindow* inputWindow);
	bool checkNeighbors(int x, int y);

	//MAP GENERATION//////////////////
	int generateMap();
	int generateNames();
	int generatePrecipAndTemp();

		//Political//////////////////
		std::vector <country> listOfCountries;
		std::vector<province> listOfProvinces;
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


};


#endif /* MASTERBOARD_HPP__ */

