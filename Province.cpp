#include "Province.hpp"

/*
int province::updateProvincePopulation() 
{

	//First update provincial growth modifiers
	double ruralGrowthRate = 0;
	double urbanGrowthRate = 0;

	//AgriproductivityBonus x 2
	listOfUrbanPopGrowthModifiers[1].GrowthModiferValue = 2 * techLevelAgriBonus[provinceTechLevel];
	listOfRuralPopGrowthModifiers[1].GrowthModiferValue = 2 * techLevelAgriBonus[provinceTechLevel];

	//Add all factors to rural growth rate.
	for (int i = 0; i < 2; i++)
		ruralGrowthRate += listOfRuralPopGrowthModifiers[i].GrowthModiferValue;

	//If at max AND positive growth, then urban growth factor gets rural growth rate added to it.
	if (ruralPopulation >= maxRuralPopulation && ruralGrowthRate > 0)
	{
		listOfUrbanPopGrowthModifiers[2].GrowthModiferValue = ruralGrowthRate;
	}
	else //If not max pop
	{
		double pop = ruralPopulation;
		ruralPopulation = int(pop * (1 + ruralGrowthRate / 100));
	}
	//If we hit the max afterwards, set to max.
	if (ruralPopulation > maxRuralPopulation)
	{
		ruralPopulation = maxRuralPopulation;
	}

	//Insert war and building effects here.

	//First update urban max based on CURRENT rural pop.
	maxUrbanPopulation = ruralPopulation * UrbanRuralRatio[provinceTechLevel];

	//Add all factors to urban growth rate.
	for (int i = 0; i < 4; i++)
		urbanGrowthRate += listOfUrbanPopGrowthModifiers[i].GrowthModiferValue;
	if (urbanPopulation < maxUrbanPopulation)
	{
		double pop = urbanPopulation;
		urbanPopulation = int(pop * (1 + urbanGrowthRate / 100));
	}
	//If we hit the max afterwards, set to max.
	if (urbanPopulation > maxUrbanPopulation)
	{
		urbanPopulation = maxUrbanPopulation;
	}

	return 1;



}
*/