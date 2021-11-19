#include "Mission.h"
#include <stdexcept>
 
const Point Mission::DEFAULT_COORDINATES_A = Point(-1, 1);
/*

.  |
---|---
   |

. -> A is here

*/


const Point Mission::DEFAULT_COORDINATES_B = Point(1, 1);
/*

   |  .  
---|---
   |

. -> B is here

*/


Mission::Mission() :
	commander(Captain()),
	tableConvoy(),
	tablePirates(),
	moneyAmountForMission(DEFAULT_MONEY_AMOUNT_FOR_MISSION),
	moneySpent(0),
	allWeight(DEFAULT_ALL_WEIGHT),
	minWeightToCarry(DEFAULT_MIN_WEIGHT_TO_CARRY),
	lostWeight(0),
	carriedWeight(0),
	maxCountOfShipsConvoy(DEFAULT_MAX_COUNT_OF_SHIPS_CONVOY),
	maxCountOfShipsPirates(DEFAULT_MAX_COUNT_OF_SHIPS_PIRATES),
	sizeA(DEFAULT_SIZE_A),
	coordinatesA(DEFAULT_COORDINATES_A),
	sizeB(DEFAULT_SIZE_B),
	coordinatesB(DEFAULT_COORDINATES_B),
	coordinatesOfPiratesBases(),
	piratesSpawnInterval(DEFAULT_PIRATES_SPAWN_INTERVAL)
{}


Mission::Mission(
	const Captain& commander_,
	const Table& tableConvoy_,
	const Table& tablePirates_,
	int moneyAmountForMission_,
	int allWeight_,
	int minWeightToCarry_,
	int maxCountOfShipsConvoy_,
	int maxCountOfShipsPirates_,
	int sizeA_,
	const Point& coordinatesA_,
	int sizeB_,
	const Point& coordinatesB_,
	const std::vector<Point>& coordinatesOfPiratesBases_,
	int piratesSpawnInterval_
) :

	commander(commander_),
	tableConvoy(tableConvoy_),
	tablePirates(tablePirates_),
	moneyAmountForMission(moneyAmountForMission_),
	moneySpent(0),
	allWeight(allWeight_),
	minWeightToCarry(minWeightToCarry_),
	lostWeight(0),
	carriedWeight(0),
	maxCountOfShipsConvoy(maxCountOfShipsConvoy_),
	maxCountOfShipsPirates(maxCountOfShipsPirates_),
	sizeA(sizeA_),
	coordinatesA(coordinatesA_),
	sizeB(sizeB_),
	coordinatesB(coordinatesB_),
	coordinatesOfPiratesBases(coordinatesOfPiratesBases_),
	piratesSpawnInterval(piratesSpawnInterval_)
{}



Ship* Mission::getShipByID(int id, Mission::Teams team) const
{
	if (team == Mission::Teams::Convoy)
	{
		return tableConvoy.getShipByID(id);
	}

	else if (team == Mission::Teams::Pirates)
	{
		return tablePirates.getShipByID(id);
	}

	return nullptr;
}


Mission& Mission::createBattlePirateShip()
{
	tablePirates.addShip(new SecurityShip);
	return *this;
}


Mission& Mission::buyConvoyShip(ShipTypes typeOfConvoyShip)
{
	//! TO DO: insert actions here
	return *this;
}


Mission& Mission::sellConvoyShip(int id)
{
	//! TO DO: insert actions here
	return *this;
}


Mission& Mission::buyWeaponInPlace(int shipID, Mission::Teams team, WeaponTypes type, Mission::WeaponPlaces place)
{
	//! TO DO: insert actions here
	return *this;
}


Mission& Mission::sellWeaponInPlace(int shipID, Mission::Teams team, WeaponTypes type, Mission::WeaponPlaces place)
{
	//! TO DO: insert actions here
	return *this;
}


Mission& Mission::destroyShipByID(int shipID, Mission::Teams team)
{
	if (team == Mission::Teams::Convoy)
	{
		tableConvoy.removeShip(shipID);
	}

	else if (team == Mission::Teams::Pirates)
	{
		tablePirates.removeShip(shipID);
	}

	return *this;
}


Mission& Mission::setWeightToShip(int shipID)
{
	//! TO DO: insert actions here
	return *this;
}


Mission& Mission::automaticConvoyLoad()
{
	//! TO DO: insert actions here
	return *this;
}



