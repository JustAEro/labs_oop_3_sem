#pragma once
#include "../Table/TableElement.h"

class Mission
{
private:

	Captain commander;

	Table tableConvoy;
	Table tablePirates;

	int moneyAmountForMission;
	int moneySpent;

	int allWeight;
	int minWeightToCarry;
	int lostWeight;
	int carriedWeight;

	int maxCountOfShipsConvoy;
	int maxCountOfShipsPirates;

	int sizeA;
	Point coordinatesA;

	int sizeB;
	Point coordinatesB;

	std::vector <Point> coordinatesOfPiratesBases;
	int piratesSpawnInterval;

public:

	//getters

	//setters

	Ship* getShipByID(int id);
	Mission& modifyShipByID(int id);

	Mission& createBattlePirateShip();

	Mission& buyConvoyShip();
	Mission& sellConvoyShip();

	Mission& buyWeaponInPlace
		(int shipID, WeaponTypes type, int numberOfPlace);

	Mission& sellWeaponInPlace
		(int shipID, WeaponTypes type, int numberOfPlace);

	Mission& destroyShipByID(int shipID);
	Mission& setWeightToShip(int shipID);
	Mission& automaticConvoyLoad();
};

