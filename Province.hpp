#ifndef PROVINCE_HPP__
#define PROVINCE_HPP__

#include <vector>

enum techLevel: int { PreIndustrial = 1, Industrial = 2, Mechanized = 3, Modern  = 4};

//The zero value here is garbage.
const double techLevelAgriBonus[5] = {-100, 1,2,3,4 };
const double UrbanRuralRatio[5] = {-100, 0.2, 1, 5, 10 };


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

struct growthModifiers 
{

	std::string GrowthModifierType = "";

	double GrowthModiferValue = 0; 
};


class province
{
public:

	province()
	{
		numberOfSquares = 0;
		ruralPopulation = 0;
		urbanPopulation = 0;

		maxRuralPopulation = 0;
		maxUrbanPopulation = 0;

		name = "UNKNOWN";
		controller = 0;
		listOfTiles.clear();

		provinceTechLevel = Industrial;

	}

	//War - 5% for now.
	//RuralPopAtMax - Add whatever it would be for rural, to the urban growth.
	//AgriProductivity - 2xTechLevelAgriBonus
	growthModifiers listOfUrbanGrowthModifiers[4]  = {	{"WarModifier", 0 },
													{"AgriProductivityX2",0 },
													{"RuralPopAtMaxBonus", 0} ,
													{"NumberOfBuildings", 0} };

	growthModifiers listOfRuralGrowthModifiers[4] = { {"WarModifier", 0 },
													{"AgriProductivityX2",0 } };

	int numberOfSquares = 0;
	int ruralPopulation = 0;
	int urbanPopulation = 0;

	int maxRuralPopulation = 0;
	int maxUrbanPopulation = 0;

	techLevel provinceTechLevel = Industrial;
	std::string name;
	int controller = 0;
	std::vector <xyCoord> listOfTiles;

};



#endif /* PROVINCE_HPP__*/