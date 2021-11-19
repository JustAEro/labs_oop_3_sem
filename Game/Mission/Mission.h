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


	static int constexpr DEFAULT_MAX_COUNT_OF_SHIPS_CONVOY = 20;
	static int constexpr DEFAULT_MAX_COUNT_OF_SHIPS_PIRATES = 20;


public:

	enum class Teams
	{
		Convoy,
		Pirates
	};

	enum class WeaponPlaces
	{
		Stern,
		Nose,
		LeftSide,
		RightSide
	};


	static int constexpr DEFAULT_MONEY_AMOUNT_FOR_MISSION = 1000;
	static int constexpr DEFAULT_ALL_WEIGHT = 100;
	static int constexpr DEFAULT_MIN_WEIGHT_TO_CARRY = 60;

	static int constexpr DEFAULT_SIZE_A = 5;
	static const Point DEFAULT_COORDINATES_A;  //defined in .cpp file
	static int constexpr DEFAULT_SIZE_B = 5;
	static const Point DEFAULT_COORDINATES_B;  //defined in .cpp file

	static int constexpr DEFAULT_PIRATES_SPAWN_INTERVAL = 30000;  //30000 milliseconds == 30 seconds


	Mission();

	Mission(
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
	);
		
	//getters
	const Captain& getCommander()	const noexcept { return commander; }
	const Table& getTableConvoy()	const noexcept { return tableConvoy; }
	const Table& getTablePirates()  const noexcept { return tablePirates; }
	int getMoneyAmountForMission()  const noexcept { return moneyAmountForMission; }
	int getAllWeight()				const noexcept { return allWeight; }
	int getMinWeightToCarry()		const noexcept { return minWeightToCarry; }
	int getMaxCountOfShipsConvoy()	const noexcept { return maxCountOfShipsConvoy; }
	int getMaxCountOfShipsPirates() const noexcept { return maxCountOfShipsPirates; }
	int getSizeA()					const noexcept { return sizeA; }
	const Point& getCoordinatesA()	const noexcept { return coordinatesA; }
	int getSizeB()					const noexcept { return sizeB; }
	const Point& getCoordinatesB()	const noexcept { return coordinatesB; }
	const std::vector<Point>& getCoordinatesOfPiratesBases() const noexcept { return coordinatesOfPiratesBases; }
	int getPiratesSpawnInterval()	const noexcept { return piratesSpawnInterval; }

	//setters
	Mission& setCommander(const Captain& commander_)				{ commander = commander_; }
	Mission& setTableConvoy(const Table& tableConvoy_)				{ tableConvoy = tableConvoy_; }
	Mission& setTablePirates(const Table& tablePirates_)			{ tablePirates = tablePirates_; }
	Mission& setMoneyAmountForMission(int moneyAmountForMission_)	{ moneyAmountForMission = moneyAmountForMission_; }
	Mission& setAllWeight(int allWeight_)							{ allWeight = allWeight_; }
	Mission& setMinWeightToCarry(int minWeightToCarry_)				{ minWeightToCarry = minWeightToCarry_; }
	Mission& setMaxCountOfShipsConvoy(int maxCountOfShipsConvoy_)	{ maxCountOfShipsConvoy = maxCountOfShipsConvoy_; }
	Mission& setMaxCountOfShipsPirates(int maxCountOfShipsPirates_) { maxCountOfShipsPirates = maxCountOfShipsPirates_; }
	Mission& setSizeA(int sizeA_)									{ sizeA = sizeA_; }
	Mission& setCoordinatesA(const Point& coordinatesA_)			{ coordinatesA = coordinatesA_; }
	Mission& setSizeB(int sizeB_)									{ sizeB = sizeB_; }
	Mission& setCoordinatesB(const Point& coordinatesB_)			{ coordinatesB = coordinatesB_; }
	Mission& setCoordinatesOfPiratesBases(const std::vector<Point>& coordinatesOfPiratesBases_) { coordinatesOfPiratesBases = coordinatesOfPiratesBases_; }
	Mission& setPiratesSpawnInterval(int piratesSpawnInterval_)		{ piratesSpawnInterval = piratesSpawnInterval_; }



	Ship* getShipByID(int id, Teams team) const;

	Mission& createBattlePirateShip();

	Mission& buyConvoyShip(ShipTypes typeOfConvoyShip);
	Mission& sellConvoyShip(int id);

	Mission& buyWeaponInPlace (int shipID, Teams team, WeaponTypes type, WeaponPlaces place);

	Mission& sellWeaponInPlace (int shipID, Teams team, WeaponTypes type, WeaponPlaces place);

	Mission& destroyShipByID(int shipID, Teams team);
	Mission& setWeightToShip(int shipID);
	Mission& automaticConvoyLoad();
};

