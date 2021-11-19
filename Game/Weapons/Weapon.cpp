#include "Weapon.h"

Weapon::Weapon() : 
	type (WeaponTypes::Light), 
	damage (DEFAULT_LIGHT_WEAPON_DAMAGE),
	fireRate (DEFAULT_LIGHT_WEAPON_FIRE_RATE),
	currentAmmo (DEFAULT_LIGHT_WEAPON_MAX_AMMO),
	maxAmmo (DEFAULT_LIGHT_WEAPON_MAX_AMMO),
	cost (DEFAULT_LIGHT_WEAPON_COST),
	fireRange (DEFAULT_LIGHT_WEAPON_FIRE_RANGE),
	isShooting(false)
{}

Weapon::Weapon(WeaponTypes type_) : isShooting(false)
{
	if (type_ == WeaponTypes::Light)
	{
		type = WeaponTypes::Light;
		damage = DEFAULT_LIGHT_WEAPON_DAMAGE;
		fireRate = DEFAULT_LIGHT_WEAPON_FIRE_RATE;
		currentAmmo = DEFAULT_LIGHT_WEAPON_MAX_AMMO;
		maxAmmo = DEFAULT_LIGHT_WEAPON_MAX_AMMO;
		cost = DEFAULT_LIGHT_WEAPON_COST;
		fireRange = DEFAULT_LIGHT_WEAPON_FIRE_RANGE;
	}

	else if (type_ == WeaponTypes::Medium)
	{
		type = WeaponTypes::Medium,
		damage = DEFAULT_MEDIUM_WEAPON_DAMAGE,
		fireRate = DEFAULT_MEDIUM_WEAPON_FIRE_RATE,
		currentAmmo = DEFAULT_MEDIUM_WEAPON_MAX_AMMO,
	    maxAmmo = DEFAULT_MEDIUM_WEAPON_MAX_AMMO,
		cost = DEFAULT_MEDIUM_WEAPON_COST,
		fireRange = DEFAULT_MEDIUM_WEAPON_FIRE_RANGE;
	}

	else if (type_ == WeaponTypes::Heavy)
	{
		type = WeaponTypes::Heavy;
		damage = DEFAULT_HEAVY_WEAPON_DAMAGE;
		fireRate = DEFAULT_HEAVY_WEAPON_FIRE_RATE;
		currentAmmo = DEFAULT_HEAVY_WEAPON_MAX_AMMO;
		maxAmmo = DEFAULT_HEAVY_WEAPON_MAX_AMMO;
		cost = DEFAULT_HEAVY_WEAPON_COST;
		fireRange = DEFAULT_HEAVY_WEAPON_FIRE_RANGE;
	}

	else
	{
		throw std::logic_error("Invalid weapon type");
	}

}



Weapon& Weapon::setType(WeaponTypes type_)
{
	type = type_;
	return *this;
}

Weapon& Weapon::setDamage(int damage_)
{
	damage = damage_;
	return *this;
}

Weapon& Weapon::setFireRate(int fireRate_)
{
	fireRate = fireRate_;
	return *this;
}

Weapon& Weapon::setCurrentAmmo(int curAmmo_)
{
	if (curAmmo_ > maxAmmo) 
	{
		throw std::logic_error("Current ammo can't be larger than max ammo");
	}

	currentAmmo = curAmmo_;
	return *this;
}

Weapon& Weapon::setMaxAmmo(int maxAmmo_)
{
	maxAmmo = maxAmmo_;
	return *this;
}

Weapon& Weapon::setCost(int cost_)
{
	cost = cost_;
	return *this;
}

Weapon& Weapon::setFireRange(int range_)
{
	fireRange = range_;
	return *this;
}

Weapon& Weapon::setIsShooting(bool status_)
{
	isShooting = status_;
	return *this;
}



int Weapon::shoot()
{
	if (currentAmmo == 0)
	{
		return 0;
	}

	isShooting = true;
	
	int count_of_shots = 0;
	for (int i = 0; i < fireRate && currentAmmo > 0; ++i)
	{
		--currentAmmo;
		++count_of_shots;
	}
	
	isShooting = false;

	return damage*count_of_shots;
}


