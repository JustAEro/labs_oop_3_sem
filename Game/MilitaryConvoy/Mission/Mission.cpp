#include "Mission.h"
#include <stdexcept>
 
const Point Mission::DEFAULT_COORDINATES_A = Point(-1, 1);
/*

A  |
---|---
   |

. -> A is here

*/


const Point Mission::DEFAULT_COORDINATES_B = Point(1, -1);
/*

   |    
---|---
   |  B

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


int Mission::createBattlePirateShip()
{
	int id_res = tablePirates.addShip(new SecurityShip);
	return id_res;
}


int Mission::buyConvoyShip(ShipTypes typeOfConvoyShip)
{
	int id_res;

	if (typeOfConvoyShip == ShipTypes::SecurityShip)
	{
		if (moneySpent + SecurityShip::DEFAULT_COST > moneyAmountForMission)
		{
			throw std::logic_error("Not enough money");
		}

		id_res = tableConvoy.addShip(new SecurityShip);
		moneySpent += SecurityShip::DEFAULT_COST;
	}


	else if (typeOfConvoyShip == ShipTypes::TransportShip)
	{
		if (moneySpent + TransportShip::DEFAULT_COST > moneyAmountForMission)
		{
			throw std::logic_error("Not enough money");
		}

		id_res = tableConvoy.addShip(new TransportShip);
		moneySpent += TransportShip::DEFAULT_COST;
	}


	else if (typeOfConvoyShip == ShipTypes::BattleTransport)
	{
		if (moneySpent + BattleTransport::DEFAULT_COST > moneyAmountForMission)
		{
			throw std::logic_error("Not enough money");
		}
		id_res = tableConvoy.addShip(new BattleTransport);
		moneySpent += BattleTransport::DEFAULT_COST;
	}

	else
	{
		throw std::logic_error("Invalid type of ship");
	}
	
	return id_res;
}


Mission& Mission::sellConvoyShip(int id)
{
	Ship* convoyShipToSell = tableConvoy.getShipByID(id);
	if (convoyShipToSell == nullptr)
	{
		throw std::logic_error("Ship to sell not found");
	}

	moneySpent -= convoyShipToSell->getCost();
	tableConvoy.removeShip(id);

	return *this;
}


Mission& Mission::buyWeaponInPlace(int shipID, WeaponTypes type, Mission::WeaponPlaces place)
{
	Ship* shipToBuyWeapon = tableConvoy.getShipByID(shipID);

	if (shipToBuyWeapon == nullptr)
	{
		throw std::logic_error("Ship to buy weapon not found");
	}

	ShipTypes typeOfShip = shipToBuyWeapon->getType();

	if (typeOfShip == ShipTypes::TransportShip)
	{
		throw std::logic_error("You can't set weapon to transport ship");
	}

	if (typeOfShip == ShipTypes::SecurityShip)
	{
		SecurityShip* cur = static_cast<SecurityShip*>(shipToBuyWeapon);
		SecurityShip::WeaponPlaces placeToSet = static_cast<SecurityShip::WeaponPlaces>(place);

		Weapon* weaponToAdd = new Weapon(type);

		moneySpent += weaponToAdd->getCost();
		cur->addWeapon(placeToSet, weaponToAdd);
	}

	else  //BattleTransport 
	{
		BattleTransport* cur = static_cast<BattleTransport*>(shipToBuyWeapon);
		BattleTransport::WeaponPlaces placeToSet = static_cast<BattleTransport::WeaponPlaces>(place);

		Weapon* weaponToAdd = new Weapon(type);

		moneySpent += weaponToAdd->getCost();
		cur->addWeapon(placeToSet, weaponToAdd);
	}

	return *this;
}


Mission& Mission::sellWeaponInPlace(int shipID, WeaponTypes type, Mission::WeaponPlaces place)
{
	Ship* shipToSellWeapon = tableConvoy.getShipByID(shipID);

	if (shipToSellWeapon == nullptr)
	{
		throw std::logic_error("Ship to sell weapon not found");
	}

	ShipTypes typeOfShip = shipToSellWeapon->getType();

	if (typeOfShip == ShipTypes::TransportShip)
	{
		throw std::logic_error("You can't sell weapon of transport ship. It doesn't contain weapons.");
	}

	if (typeOfShip == ShipTypes::SecurityShip)
	{
		SecurityShip* cur = static_cast<SecurityShip*>(shipToSellWeapon);
		SecurityShip::WeaponPlaces placeToSell = static_cast<SecurityShip::WeaponPlaces>(place);

		moneySpent -= cur->getWeaponInfo(placeToSell)->getCost();
		cur->removeWeapon(placeToSell);
	}

	else  //BattleTransport 
	{
		BattleTransport* cur = static_cast<BattleTransport*>(shipToSellWeapon);
		BattleTransport::WeaponPlaces placeToSell = static_cast<BattleTransport::WeaponPlaces>(place);

		moneySpent -= cur->getWeaponInfo(placeToSell)->getCost();
		cur->removeWeapon(placeToSell);
	}

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


Mission& Mission::setWeightToShip(int shipID, int weight)
{
	Ship* shipToSetWeight = tableConvoy.getShipByID(shipID);

	if (shipToSetWeight == nullptr)
	{
		throw std::logic_error("Ship to set weight not found");
	}


	ShipTypes typeOfShip = shipToSetWeight->getType();

	if (typeOfShip == ShipTypes::SecurityShip)
	{
		throw std::logic_error("Security ship can't carry any weight");
	}
	

	TransportShip* cur = static_cast<TransportShip*>(shipToSetWeight);
	cur->setWeight(weight);

	return *this;
}


Mission& Mission::automaticConvoyLoad()
{
	//! TO DO: insert actions here
	
	int countOfTransports = 0;
	for (const auto& tableElement : tableConvoy)
	{
		if (tableElement.second->getType() != ShipTypes::SecurityShip)
		{
			++countOfTransports;
		}
	}

	int weightForOne = allWeight / countOfTransports;

	
	int packedWeight = 0;

	for (const auto& tableElement : tableConvoy)
	{
		Ship* curShip = tableElement.second;
		
		if (curShip->getType() == ShipTypes::SecurityShip)
		{
			continue;
		}

		else
		{
			TransportShip* curTransport = static_cast<TransportShip*>(curShip);

			try 
			{
				curTransport->setWeight(weightForOne);
			}
			catch (const std::logic_error& er)
			{
				throw std::logic_error("Your convoy can't deliver this amount of cargo");
			}

			packedWeight += weightForOne;
		}
	}

	int weightLeft = allWeight - packedWeight;

	for (const auto& tableElement : tableConvoy)
	{
		Ship* curShip = tableElement.second;

		if (curShip->getType() == ShipTypes::SecurityShip)
		{
			continue;
		}

		else
		{
			TransportShip* curTransport = static_cast<TransportShip*>(curShip);
			
			try
			{
				curTransport->setWeight(curTransport->getWeight() + weightLeft);
			}
			catch (const std::logic_error& er)
			{
				throw std::logic_error("Your convoy can't deliver this amount of cargo");
			}
			
			break;
		}
	}

	return *this;
}



