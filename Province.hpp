#ifndef PROVINCE_HPP__
#define PROVINCE_HPP__

#include <vector>
#include <string>
#include <iostream>

enum techLevel: int { PreIndustrial = 1, Industrial = 2, Mechanized = 3, Modern  = 4};


//The zero value here is garbage.
const double techLevelAgriBonus[5] = {-100, 1,2,3,4 };
const double UrbanRuralRatio[5] = {-100, 0.2, 1, 5, 10 };
const double techLevelWealthBonus[5] = { -100, 1,3,5,10 };




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

		ruralPopulation = 0;
		urbanPopulation = 0;

		maxRuralPopulation = 0;
		maxUrbanPopulation = 0;

		ruralWealth = 0;
		urbanWealth = 0;

		name = "UNKNOWN";
		controller = 0;
		listOfTiles.clear();
		tradeRoutes.clear();

		provinceTechLevel = Industrial;

	}

	//War - 5% for now.
	//RuralPopAtMax - Add whatever it would be for rural, to the urban growth.
	//AgriProductivity - 2xTechLevelAgriBonus
	growthModifiers listOfUrbanPopGrowthModifiers[4]  = {	{"WarModifier", 0 },
													{"AgriProductivityX2",0 },
													{"RuralPopAtMaxBonus", 0} ,
													{"NumberOfBuildings", 0} };

	growthModifiers listOfRuralPopGrowthModifiers[2] = { {"WarModifier", 0 },
													{"AgriProductivityX2",0 } };

	growthModifiers listOfUrbanWealthGrowthModifiers[4] = { {"WarModifier", 0 },
														{"UrbanPopGrowth",0 },
														{"TechBonus", 0}, //(1,3, 5,10)
														{"TradeRoutes", 0} 
	};

	//Describes the physical connections between provinces. 0 indicates sea connection.
	std::vector <int> connectionsList;

	//Describes the province numbers that have a trade route with this province.
	std::vector <int >tradeRoutes;

	int ruralPopulation = 0;
	int urbanPopulation = 0;

	int maxRuralPopulation = 0;
	int maxUrbanPopulation = 0;

	int ruralWealth = 0;
	int urbanWealth = 0;

	techLevel provinceTechLevel = Industrial;
	
	double techAdvanceScore = 0;
	
	std::string name;
	int controller = 0;

	std::string provinceLog;
	
	std::vector <xyCoord> listOfTiles;

	int updateProvincePopulation();

};



#endif /* PROVINCE_HPP__*/