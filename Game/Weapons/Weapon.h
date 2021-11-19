#pragma once
#include <stdexcept>

enum class WeaponTypes
{
	Light,
	Medium,
	Heavy,

	Count
};

class Weapon
{
private:
	WeaponTypes type;
	int damage;
	int fireRate;
	int currentAmmo;
	int maxAmmo;
	int cost;
	int fireRange;
	bool isShooting;





public:

	static int constexpr DEFAULT_LIGHT_WEAPON_DAMAGE = 10;
	static int constexpr DEFAULT_LIGHT_WEAPON_FIRE_RATE = 3;
	static int constexpr DEFAULT_LIGHT_WEAPON_MAX_AMMO = 100;
	static int constexpr DEFAULT_LIGHT_WEAPON_COST = 100;
	static int constexpr DEFAULT_LIGHT_WEAPON_FIRE_RANGE = 10;

	static int constexpr DEFAULT_MEDIUM_WEAPON_DAMAGE = 20;
	static int constexpr DEFAULT_MEDIUM_WEAPON_FIRE_RATE = 2;
	static int constexpr DEFAULT_MEDIUM_WEAPON_MAX_AMMO = 50;
	static int constexpr DEFAULT_MEDIUM_WEAPON_COST = 200;
	static int constexpr DEFAULT_MEDIUM_WEAPON_FIRE_RANGE = 20;

	static int constexpr DEFAULT_HEAVY_WEAPON_DAMAGE = 30;
	static int constexpr DEFAULT_HEAVY_WEAPON_FIRE_RATE = 1;
	static int constexpr DEFAULT_HEAVY_WEAPON_MAX_AMMO = 10;
	static int constexpr DEFAULT_HEAVY_WEAPON_COST = 300;
	static int constexpr DEFAULT_HEAVY_WEAPON_FIRE_RANGE = 30;
	

	Weapon();
	Weapon(WeaponTypes type_);
	

	//getters
	WeaponTypes getType() const noexcept { return type; }
	int getDamage() const noexcept { return damage; }
	int getFireRate() const noexcept { return fireRate; }
	int getCurrentAmmo() const noexcept { return currentAmmo; }
	int getMaxAmmo() const noexcept { return maxAmmo; }
	int getCost() const noexcept { return cost; }
	int getFireRange() const noexcept { return fireRange; }
	bool getIsShooting() const noexcept { return isShooting; }

	//setters
	Weapon& setType(WeaponTypes type_);
	Weapon& setDamage(int damage_);
	Weapon& setFireRate(int fireRate_);
	Weapon& setCurrentAmmo(int curAmmo_);
	Weapon& setMaxAmmo(int maxAmmo_);
	Weapon& setCost(int cost_);
	Weapon& setFireRange(int range_);
	Weapon& setIsShooting(bool status_);
	//...........................


	int shoot();  //returns fireRate*(damage of 1 shot) 
};

