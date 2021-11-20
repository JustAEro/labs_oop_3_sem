#pragma once
#include <string>
#include <array>
#include <cmath>
#include "../Weapons/Weapon.h"

enum class CaptainRanks
{
	First,
	Second,
	Third,

	Count,
};

struct Captain
{
	std::string fullName;
	CaptainRanks rank;

	Captain() : fullName(std::string("")), rank(CaptainRanks::First)
	{}

	Captain(const std::string& name, CaptainRanks captainRank) : fullName(name), rank(captainRank)
	{}
};

bool operator== (const Captain& cap1, const Captain& cap2);
bool operator!= (const Captain& cap1, const Captain& cap2);


enum class ShipTypes
{
	SecurityShip,
	TransportShip,
	BattleTransport,

	Count,
};

struct Point
{
	int x;
	int y;

	Point() : x(0), y(0) {}
	Point(int x_, int y_): x(x_), y(y_) {}

};

bool operator== (const Point& p1, const Point& p2);
bool operator!= (const Point& p1, const Point& p2);

double distanceBetweenTwoPoints(const Point& a, const Point& b);



/*!
	\brief Abstract class Ship

	This class implements basic interface for different types of ships
*/

class Ship
{
protected:

	Captain captain;
	int maxVelocity;
	int currentVelocity;
	int maxHP;
	int currentHP;
	int cost;
	Point coordinatesOfShip;  //? maybe better in Ship.h ?

public:
	
	Ship(const Captain& cap, int maxVel, int maxHPForType, int costOfType, const Point& coords) : 
		captain(cap), maxVelocity(maxVel), currentVelocity(0), maxHP(maxHPForType), currentHP(maxHPForType),
		cost(costOfType), coordinatesOfShip(coords)
	{}

	virtual ShipTypes getType() const = 0;

	//getters
	const Captain& getCaptain() const noexcept { return captain; }
	int getMaxVelocity() const noexcept { return maxVelocity; }    //! make virtual
	int getCurrentVelocity() const noexcept { return currentVelocity; }
	int getMaxHP() const noexcept { return maxHP; }
	int getCurrentHP() const noexcept { return currentHP; }
	int getCost() const noexcept { return cost; }
	const Point& getCoordinates() const noexcept { return coordinatesOfShip; }


	//setters
	Ship& setCaptain(const Captain& cap_);
	Ship& setMaxVelocity(int maxVelocity_);
	Ship& setCurrentVelocity(int vel_);
	Ship& setMaxHP(int maxHP_);
	Ship& setCurrentHP(int hp_);
	Ship& setCost(int cost_);
	Ship& setCoordinates(const Point& coords_);

	Ship& takeDamage(int damage);

	virtual ~Ship() {};
};



class SecurityShip : public Ship
{
private:
	static constexpr int COUNT_OF_PLACES = 4;
	std::array <Weapon*, COUNT_OF_PLACES> availableWeaponPlaces;

public:

	enum class WeaponPlaces
	{
		Stern,
		Nose,
		LeftSide,
		RightSide
	};


	static constexpr int DEFAULT_MAX_VELOCITY = 3;
	static constexpr int DEFAULT_MAX_HP = 100;
	static constexpr int DEFAULT_COST = 300;

	SecurityShip():
		Ship(Captain(), DEFAULT_MAX_VELOCITY, DEFAULT_MAX_HP, DEFAULT_COST, Point(0,0))
	{
		for (size_t i = 0; i < COUNT_OF_PLACES; ++i)
		{
			availableWeaponPlaces[i] = nullptr;
		}
	}

	SecurityShip(const Captain& cap, const Point& coords) : SecurityShip()
	{
		captain = cap;
		coordinatesOfShip = coords;
	}

	virtual ShipTypes getType() const override
	{
		return ShipTypes::SecurityShip;
	}


	const Weapon* getWeaponInfo(WeaponPlaces place_) const;


	SecurityShip& addWeapon(WeaponPlaces place_, Weapon* weapon_);
	SecurityShip& removeWeapon(WeaponPlaces place_);
	

	int shootToPoint(const Point&) const;


	~SecurityShip();
};



class TransportShip : public Ship
{
protected:
	int maxWeight;
	int currentWeight;
	int ratio; 
	//the coefficient of reducing the speed of the ship depending on the load

	TransportShip& calculateMaxVelocity();



public:

	static constexpr int DEFAULT_MAX_VELOCITY = 2;
	static constexpr int DEFAULT_MAX_HP = 300;
	static constexpr int DEFAULT_COST = 400;
	static constexpr int DEFAULT_MAX_WEIGHT = 10;
	static constexpr int DEFAULT_RATIO = 1;

	TransportShip() :
		Ship(Captain(), DEFAULT_MAX_VELOCITY, DEFAULT_MAX_HP, DEFAULT_COST, Point(0,0)), 
		maxWeight(DEFAULT_MAX_WEIGHT), 
		currentWeight(0), 
		ratio(DEFAULT_RATIO)
	{}


	TransportShip(const Captain& cap, const Point& coords) : TransportShip()
	{
		captain = cap;
		coordinatesOfShip = coords;
	}


	virtual ShipTypes getType() const override
	{
		return ShipTypes::TransportShip;
	}

	int getWeight() const { return currentWeight; }
	
	TransportShip& setWeight(int weight);


	virtual ~TransportShip() {};
};


class BattleTransport : public TransportShip
{
private:
	static const int COUNT_OF_PLACES = 4;
	std::array <Weapon*, COUNT_OF_PLACES> availableWeaponPlaces;
	

public:

	enum class WeaponPlaces
	{
		Stern,
		Nose,
		LeftSide,
		RightSide
	};

	static constexpr int DEFAULT_MAX_VELOCITY = 2;
	static constexpr int DEFAULT_MAX_HP = 200;
	static constexpr int DEFAULT_COST = 500;
	static constexpr int DEFAULT_MAX_WEIGHT = 10;
	static constexpr int DEFAULT_RATIO = 1;

	BattleTransport() : TransportShip(Captain(), Point(0,0))
	{
		for (size_t i = 0; i < COUNT_OF_PLACES; ++i)
		{
			availableWeaponPlaces[i] = nullptr;
		}
	}

	BattleTransport(const Captain& cap, const Point& coords) : BattleTransport()
	{
		captain = cap;
		coordinatesOfShip = coords;
	}

	virtual ShipTypes getType() const override
	{
		return ShipTypes::BattleTransport;
	}

	const Weapon* getWeaponInfo (WeaponPlaces place_) const;

	BattleTransport& addWeapon(WeaponPlaces place_, Weapon* weapon_);
	BattleTransport& removeWeapon(WeaponPlaces place_);

	int shootToPoint(const Point&) const;


	~BattleTransport();
};

