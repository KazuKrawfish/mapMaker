#include "MasterBoard.hpp"
#include <string>
#include <iostream>
#include "inputLayer.hpp"
#include <cmath>
#include "mainmenu.h"
#include <iostream>
#include <fstream>



MasterBoard::MasterBoard(sf::Texture *inputTexture, sf::RenderWindow* inputWindow )
{
	myTexture = inputTexture;
	myWindow = inputWindow;

	Board.resize(BOARD_WIDTH + 1);
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		Board[i].resize(BOARD_HEIGHT);
	}

	listOfCountries.resize(numberOfCountries+1);

	listOfProvinces.resize(numberOfProvinces+1);

	return;
}

int MasterBoard::clearBoard()
{
	//Clear countries and provinces
	listOfCountries.clear();
	listOfCountries.resize(numberOfCountries + 1);

	listOfProvinces.clear();
	listOfProvinces.resize(numberOfProvinces + 1);

	//Clear map
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			Board[x][y].clearTile();
		}
	}

	return 0;
}

//Ensures cursor stays within the window.
//Should work?
int MasterBoard::checkWindow()
{

	//Incremental moves
	/*sf::Vector2i mousePosition = sf::Mouse::getPosition(*myWindow);
	if (mousePosition.x == (windowLocationX) && mousePosition.x != 0)						//If the cursor moves to the left edge of the window AND it's not at the edge of the board
		windowLocationX--;																			//Shift the window left
	if (mousePosition.x == (windowLocationX + WINDOW_WIDTH - 1) && (windowLocationX + WINDOW_WIDTH != BOARD_WIDTH))		//If the cursor moves to the right edge of the window AND it's not at the edge of the board
		windowLocationX++;																																//Shift the window to the right
	if (mousePosition.y == windowLocationY && mousePosition.y != 0)						//If the cursor moves to the top edge of the window AND it's not at the edge of the board
		windowLocationY--;																//Shift the window up.
	if ( mousePosition.y == (windowLocationY + WINDOW_HEIGHT - 1) && (windowLocationY + WINDOW_HEIGHT != BOARD_HEIGHT))				//If the cursor moves to the bottom of the window AND it's not at the bottom of the board
		windowLocationY++;																														//Shift the window down once.
		*/

	return 0;
}

//Generates a map by creating a 2D normal distribution and adding to an random-walk-esque 2D heightmap, which provides some element of coherent noise. 
//This provides an elevation map that is pseudo-coherent but also roughly centered on the center of the map, with additional outlying islands also thrown in.
//The province map is a set of randomly centered 2D normal distributions that determine control of individual tiles.
//These tiles are then checked to ensure they're contiguous with the at least one other tile of the province.
//Each province is then randomly assigned to a country.
int MasterBoard::generateMap()
{
	std::ofstream myfile;
	myfile.open("./log.txt");
	if (myfile.is_open() == false)
		std::cout << "failed open" << std::endl;
	else std::cout << "succesfful open" << std::endl;
	
	myfile << "Writing this to a file.\n";

	//Initialize two 2D random vectors.
	std::vector < std::vector <int>> randwalkArray;
	randwalkArray.resize(BOARD_WIDTH + 1);
	for (int i = 0; i < BOARD_WIDTH; i ++ )
		randwalkArray[i].resize(BOARD_HEIGHT + 1);
	
	std::vector < std::vector <int>> normalArray;
	normalArray.resize(BOARD_WIDTH + 1);
	for (int i = 0; i < BOARD_WIDTH; i++)
		normalArray[i].resize(BOARD_HEIGHT + 1);
	
	//Resize board
	Board.resize(BOARD_WIDTH + 1);
	for (int i = 0; i < BOARD_WIDTH; i++)
		Board[i].resize(BOARD_HEIGHT + 1);

	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			//Resize and reset province control points
			Board[x][y].provinceControlPoints.resize(numberOfProvinces + 1, 0 );
		}
	}

	//Find means for 2D normalArray
	double meanX = BOARD_WIDTH / 2;
	double meanY = BOARD_HEIGHT / 2;

	//Total size of range for rand (ie 20 --> -10 - 10 )
	int randSize = 20;

	//Adds in a little more random to break up the coherence. Should be no more than 1/4 randSize.
	int incoherenceFactor = 2;

	//SuperContinentWeight supports a large continent in the middle of the screen.
	//Recommended between 3-5
	int SuperContinentWeight = 5;
	
	// Use current time as seed for random generator
	srand(time(0));
	std::random_device rd{};
	std::mt19937 gen{ rd() };

	//Perform normal distribution for main continent
	for (int n = 0; n < BOARD_HEIGHT * BOARD_WIDTH * 3; ++n)
	{
		std::normal_distribution<> disX{ meanX,meanX / 3 };
		std::normal_distribution<> disY{ meanY,meanY / 3 };

		int x = std::round(disX(gen));
		int y = std::round(disY(gen));
		if (x > 0 && y > 0 && x < BOARD_WIDTH - 1 && y < BOARD_HEIGHT - 1)
			++normalArray[x][y];
	}


	//Perform normal distro for outlying islands/random points.
	for (int i = 0; i < 2; i++)
	{
		double centerX = rand() % BOARD_WIDTH;
		double centerY = rand() % BOARD_HEIGHT;

		std::normal_distribution<> newX{ centerX,2 };
		std::normal_distribution<> newY{ centerY,2 };

		//Perform normal distribution
		for (int n = 0; n < BOARD_HEIGHT * BOARD_WIDTH * 2; ++n)
		{
			int x = std::round(newX(gen));
			int y = std::round(newY(gen));
			if (x > 0 && y > 0 && x < BOARD_WIDTH  && y < BOARD_HEIGHT - 1)
				++normalArray[x][y];
		}
	}


//Finalize normal array by subtracting some constant number to "normalize".
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{

			normalArray[i][y] -= (meanX / 2 + meanY / 2);

		}
		std::cout << std::endl;
	}


	//For each element, provide random value from -20 to 20 and add to previous value.
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{

			int localValue = randSize - (rand() % (2 * randSize + 1));
			//std::cout<<localValue<<std::endl;
			bool localExtreme = false;

			//Attempt to add in Char. 3. If localValue is extremely large or small, it will cause significant shift in the array's actual value.

			if (localValue > (randSize - incoherenceFactor) || (localValue < -(randSize - incoherenceFactor)))
			{
				randwalkArray[i][y] = localValue * 3;
				localExtreme = true;
			}
			else
				randwalkArray[i][y] = localValue;


			if (i > 0 && localExtreme == false)
			{
				randwalkArray[i][y] += randwalkArray[i - 1][y] / 2;
			}

			if (y > 0 && localExtreme == false)
			{
				randwalkArray[i][y] += randwalkArray[i][y - 1] / 2;

			}

			if (randwalkArray[i][y] < -99)
				randwalkArray[i][y] = -99;
			if (randwalkArray[i][y] > 99)
				randwalkArray[i][y] = 99;
		}

	//Combine normal array and random walk array for final elevation map.
	//Determine tile symbols based on elevation.
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			randwalkArray[i][y] += normalArray[i][y] * SuperContinentWeight;

			if (randwalkArray[i][y] < 0)
				Board[i][y].terrain = sea;

			Board[i][y].elevation = randwalkArray[i][y];
		}
	}

	//Find random centers for X provinces.
	//Starting at i = 1 because provinve 0 is the neutral province.
	for (int i = 1; i < numberOfProvinces + 1; i++)
	{
		double centerX = rand() % BOARD_WIDTH;
		double centerY = rand() % BOARD_HEIGHT;

		int provincePowerLevel = 4 + rand() % (2);

		std::normal_distribution<> newX{ centerX,3 };
		std::normal_distribution<> newY{ centerY,3 };

		//Perform normal distribution
		for (int n = 0; n < BOARD_HEIGHT * BOARD_WIDTH * provincePowerLevel; ++n)
		{
			int x = std::round(newX(gen));
			int y = std::round(newY(gen));
			if (x > 0 && y > 0 && x < BOARD_WIDTH   && y < BOARD_HEIGHT  )
				Board[x][y].provinceControlPoints[i]++;
		}
	}

	//Assign each square on the map a winning province based on who got more control points.
	//Must be land square.
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			int winningProvince = 0;

			for (int i = 1; i < numberOfProvinces + 1; i++)
			{
				if (randwalkArray[x][y] > 0 && Board[x][y].provinceControlPoints[i] > 0 && Board[x][y].provinceControlPoints[i] > Board[x][y].provinceControlPoints[winningProvince])
				{
					winningProvince = i;
					Board[x][y].province = winningProvince;
				}

			}

			myfile << Board[x][y].controller<<" ";
		}
		myfile << std::endl;
	}


	//Crude attempt to make all tiles within a province contiguous.
	//In the future checkNeighbors will be recursive and actally ensure the province is all one unit.
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{

			//This may change the tile
			checkNeighbors(x, y);

			//Add tile to province's tile list.
			if (Board[x][y].province != 0)
			{
				listOfProvinces[Board[x][y].province].listOfTiles.emplace_back(x, y);
				
			}

		}
	}

	//Assign provinces randomly to countries
	for (int i = 1; i < numberOfProvinces + 1; i++) 
	{
		int winnerCountry = 1 + rand() % numberOfCountries;
		listOfProvinces[i].controller = winnerCountry;
		listOfCountries[winnerCountry].listOfControlledProvinces.emplace_back(i);
		
		//Assign new controller to each tile in province.
		for (int k = 0; k < listOfProvinces[i].listOfTiles.size(); k++) 		//MAY BE ISSUE? 0 - size() inclusive enough?
		{
			Board[listOfProvinces[i].listOfTiles[k].XCoord][listOfProvinces[i].listOfTiles[k].YCoord].controller = winnerCountry;
		}
	
	}

	generateNames();

	generatePrecipAndTemp();

	myfile.close();
	return 0;
}

int MasterBoard::generateNames() 
{

	char vowelList[5] = { 'a','e','i','o','u' };
	const int startConsNum = 43;
	std::string startConsList[startConsNum] = { "B","C","D","F","G","H","J","K","L","M","N","P",
						"Q", "R","S","T","V","W","X","Y","Z","Ch", "Sh", "Kl", "Cl",    //25
						"Bl", "Fl", "Gl", "Sl", "Br","Cr", "Dr", "Fr", "Gr", "Pr", "Tr",   //36
						"Sc", "Sk", "Sm", "Sn", "St", "Sw" , "Tw"       //43
	};
	const int middleConsNum = 34;
	std::string middleConsList[middleConsNum] = { "b","c","d","f","g","h","j","k","l","m","n","p",
						"q", "r","s","t","v","w","x","y","z","ch", "sh", "lk", "sk",
						"rp","rt","rf","rp","rk", "th", "rd",
						"rg",  "st",
		//"sp", "cl", "fl", "tw" could be used in real middle but not end

	};
	std::string prefix[10] = { "Republic of ", "Empire of ", "Northern ", "Southern "
		, "Greater " , "Duchy of ", "Revolutionary ", "Dominion of ", "Confederacy of ",
		"Federation of " };
	std::string suffix[9] = { " Republic", " Empire", " Tribes", " State"
		  , " Duchy", " Revolutionary Republic", " Dominion", " Confederacy",
		" Federation" };

	std::string dryTerrainSuffix[10] = { " of Desolation", " of Joy", " of Recall", " of Thirst", " of Anger", " of Hunger", " of Sight ", " of Temptation", " of Wisdom", " of Hate" };
	std::string dryTerrainPrefix[11] = { "Desolate", "Memorial", "Ancient", "Burning", "Frozen", "Farsight", "Gentle", "Treacherous", "Rugged", "Barren", "Dusty" };

	std::string seaSuffix[7] = { " of Storms" , " of Tempests", " of Exploit" , " of Glory", " of Showers", " of Nectar" , " of Clouds" };
	std::string seaPrefix[4] = { "Stormy " , "Violent" , "Foaming " , "Known " };

	std::string forestRiverSuffix[7] = { " of Dreams" , " of Excellence", " of Hope", " of Fear" , " of Solitude", " of Sleep" , " of Decay" };
	std::string forestRiverPrefix[3] = { "Fetid " , "Harmonious ", "Mysterious " };


	// Use current time as seed for random generator
	srand(time(0));

	for (int i = 1; i < numberOfCountries + 1; i++)
	{
		std::string firstString;
		int prefixSuffixChance = rand() % 3;
		bool isPrefix = true;
		bool isSuffix = false;

		if (prefixSuffixChance == 0)
		{
			isPrefix = false;
			isSuffix = false;
		}
		else if (prefixSuffixChance == 1)
		{
			isPrefix = true;
			isSuffix = false;

		}
		else if (prefixSuffixChance == 2)
		{
			isPrefix = false;
			isSuffix = true;

		}

		if (isPrefix == true)
		{
			firstString += prefix[rand() % 10];
		}

		int componentNumber = rand() % 5;


		//Make initial name of one syllables
		firstString += startConsList[rand() % startConsNum];
		firstString += vowelList[rand() % 5];
		firstString += middleConsList[rand() % middleConsNum];

		//Almost always add a second syllable.
		if (componentNumber > 1)
		{
			firstString += vowelList[rand() % 5];
			firstString += middleConsList[rand() % middleConsNum];

			//May add another syllable to name.
			//At least another vowel, maybe another consonent set.
			if (componentNumber > 2)
			{
				firstString += vowelList[rand() % 5];
				if (componentNumber > 3)
					firstString += middleConsList[rand() % middleConsNum];
			}
		}

		if (isSuffix == true)
		{
			firstString += suffix[rand() % 9];
		}

		std::cout << firstString << std::endl;
		listOfCountries[i].name = firstString;
	}

	//Generate names for provinces.
	//No suffix/prefix. All just a name.
	for (int i = 1; i < numberOfProvinces + 1; i++)
	{
		std::string firstString;

		int componentNumber = rand() % 5;
		
		//Make initial name of one syllables
		firstString += startConsList[rand() % startConsNum];
		firstString += vowelList[rand() % 5];
		firstString += middleConsList[rand() % middleConsNum];

		//Almost always add a second syllable.
		if (componentNumber > 1)
		{
			firstString += vowelList[rand() % 5];
			firstString += middleConsList[rand() % middleConsNum];

			//May add another syllable to name.
			//At least another vowel, maybe another consonent set.
			if (componentNumber > 2)
			{
				firstString += vowelList[rand() % 5];
				if (componentNumber > 3)
					firstString += middleConsList[rand() % middleConsNum];
			}
		}

		listOfProvinces[i].name = firstString;
	}

	return 0;



}

int MasterBoard::generatePrecipAndTemp() 
{
	
	std::vector < std::vector <int>> normalPrecipArray;
	normalPrecipArray.resize(BOARD_WIDTH + 1);
	for (int i = 0; i < BOARD_WIDTH; i++)
		normalPrecipArray[i].resize(BOARD_HEIGHT + 1);

	std::vector < std::vector <int>> normalTempArray;
	normalTempArray.resize(BOARD_WIDTH + 1);
	for (int i = 0; i < BOARD_WIDTH; i++)
		normalTempArray[i].resize(BOARD_HEIGHT + 1);

	//For normalArray
	double meanX = BOARD_WIDTH / 2;
	double meanY = BOARD_HEIGHT / 2;

	// Use current time as seed for random generator
	srand(time(0));
	std::random_device rd{};
	std::mt19937 gen{ rd() };



	//Perform normal distribution in one axis for persip
	for (int n = 0; n < BOARD_HEIGHT * BOARD_WIDTH / 2; ++n)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{

			std::normal_distribution<> disY{ meanY,meanY / 3 };

			int y = std::round(disY(gen));

			if (y >= 0 && y < BOARD_HEIGHT)
				++normalPrecipArray[x][y];

		}
	}

	//Perform normal distro in 2d for "desert" and "jungle" regions that are not lattitude based.
	//Only applies to persNormalArray.
	for (int i = 0; i < 3; i++)
	{
		double  centerX = rand() % BOARD_WIDTH;
		double centerY = rand() % BOARD_HEIGHT;

		std::normal_distribution<> newX{ centerX,3 };
		std::normal_distribution<> newY{ centerY,3 };

		int value = 0;
		if (rand() % 2 == 1) { value = 1; }
		else value = -1;
		//Perform normal distribution
		for (int n = 0; n < BOARD_WIDTH * BOARD_HEIGHT * 2; ++n)
		{
			int x = std::round(newX(gen));
			int y = std::round(newY(gen));
			if (x >= 0 && y >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT)
				normalPrecipArray[x][y] += value;
		}

	}

	//Perform normal distribution in one axis for temp
	for (int n = 0; n < BOARD_WIDTH * BOARD_HEIGHT / 2; ++n)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{

			std::normal_distribution<> disY{ meanY,meanY / 3 };

			int y = std::round(disY(gen));

			if (y >= 0 && y < BOARD_HEIGHT)
				++normalTempArray[x][y];

		}
	}


	//Print out results for pers.
	for (int x = 0;x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			normalPrecipArray[x][y] -= (meanX / 2 + meanY / 2); //This is the "normalization" so the array doesn't JUST increase values
			Board[x][y].precipitation = 2*normalPrecipArray[x][y];
		}
		std::cout << std::endl;
	}

	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{

			normalTempArray[x][y] -= (meanX / 2 + meanY / 2);	//This is the "normalization" so the array doesn't JUST increase values
			Board[x][y].temperature = 3*normalTempArray[x][y];
		}
		std::cout << std::endl;
	}

	return 0;

}



//Checks each neighbor. If not one of them either has the same province number or is a sea tile, the tile in question is assigned to one of its neighbor's provinces.
bool MasterBoard::checkNeighbors(int x, int y)
{
	bool isolatedTile = true;

	if (x > 0 && Board[x - 1][y].province == Board[x][y].province)	//Any neighbors same province?
	{
		isolatedTile = false;
	}
	if (y > 0 && Board[x ][y - 1].province == Board[x][y].province)
	{
		isolatedTile = false;
	}
	if (x < BOARD_WIDTH - 1 && Board[x + 1][y].province == Board[x][y].province)
	{
		isolatedTile = false;
	}
	if (y < BOARD_HEIGHT - 1 && Board[x ][y + 1].province == Board[x][y].province)
	{
		isolatedTile = false;
	}


	//In future this will assign the province of a random valid neighboring square, but for now it simply goes in order and assigns the province of the first valid neighboring square.
	if (isolatedTile == true )
	{
		
	if (x > 0 && Board[x - 1][y].province != 0)
	{
		Board[x][y].province = Board[x - 1][y].province;
	}
	else
		if (y>0 && Board[x ][y - 1].province != 0)
		{
			Board[x][y].province = Board[x][y - 1].province ;
		}
		else
			if (x < BOARD_WIDTH - 1 && Board[x + 1][y ].province != 0)
			{
				Board[x][y].province = Board[x + 1][y].province ;
			}
			else
				if (y < BOARD_HEIGHT - 1 && Board[x ][y + 1].province != 0)
				{
					Board[x][y].province = Board[x][y + 1].province;
				}
	}
		return true;
}

int MasterBoard::initializePopulation()
{
	for (int i = 1; i < numberOfProvinces + 1; i++)
	{
		//For each province, calculate population total based on terrain/climate types.
		for (int k = 0; k < listOfProvinces[i].listOfTiles.size(); k++) 		//MAY BE ISSUE? 0 - size() inclusive enough?
		{
			listOfProvinces[i].Population +=
				(listOfProvinces[i].provinceTechLevel * 0.2 + 1) * 100 *
				Board[listOfProvinces[i].listOfTiles[k].XCoord][listOfProvinces[i].listOfTiles[k].YCoord].agriProductivity;
		}
	}

	for (int i = 1; i < numberOfCountries + 1; i++)
	{
		//For each province, calculate population total based on terrain/climate types.
		for (int k = 0; k < listOfCountries[i].listOfControlledProvinces.size(); k++) 		//MAY BE ISSUE? 0 - size() inclusive enough?
		{
			listOfCountries[i].nationalPopulation += listOfProvinces[listOfCountries[i].listOfControlledProvinces[k]].Population;
		}
		std::cout << "National pop is" << listOfCountries[i].nationalPopulation<<std::endl;
	}

	return 0;
}