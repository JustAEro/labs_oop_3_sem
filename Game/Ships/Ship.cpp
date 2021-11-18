#include "Ship.h"
#include <stdexcept>

bool operator== (const Captain& cap1, const Captain& cap2)
{
    return ((cap1.fullName == cap2.fullName) && (cap1.rank == cap2.rank));
}

bool operator!= (const Captain& cap1, const Captain& cap2)
{
    return !((cap1.fullName == cap2.fullName) && (cap1.rank == cap2.rank));
}

bool operator== (const Point& p1, const Point& p2)
{
    return ((p1.x == p2.x) && (p1.y == p2.y));
}

bool operator!= (const Point& p1, const Point& p2)
{
    return !((p1.x == p2.x) && (p1.y == p2.y));
}


double distanceBetweenTwoPoints(const Point& a, const Point& b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

Ship& Ship::setCaptain(const Captain& cap_) 
{
    captain = cap_; 
    return *this;
}

Ship& Ship::setCurrentVelocity(int vel_)
{
    if (vel_ > maxVelocity)
    {
        throw std::logic_error("Velocity can't be more than max velocity");
    }

    currentVelocity = vel_;
    return *this;
}

Ship& Ship::setCurrentHP(int hp_)
{
    if (hp_ > maxHP)
    {
        throw std::logic_error("HP can't be more than max HP");
    }
    currentHP = hp_;
    return *this;
}

Ship& Ship::setCoordinates(const Point& coords_)
{
    coordinatesOfShip = coords_;
    return *this;
}


Ship& Ship::takeDamage(int damage)
{
    currentHP -= damage;

    if (currentHP < 0)
    {
        currentHP = 0;
    }

    return *this;
}



const Weapon* SecurityShip::getWeaponInfo(WeaponPlaces place_) const
{
    unsigned int indexOfWeapon = static_cast<unsigned int>(place_);

    if (indexOfWeapon > 3)
    {
        return nullptr;
    }

    return availableWeaponPlaces[indexOfWeapon];
}



SecurityShip& SecurityShip::addWeapon(WeaponPlaces place, Weapon* weapon_)
{
    int indexOfWeapon = static_cast<int>(place);

    if (indexOfWeapon > 3)
    {
        return *this;
    }
    
    delete availableWeaponPlaces[indexOfWeapon];
    availableWeaponPlaces[indexOfWeapon] = weapon_;
    return *this;
}


SecurityShip& SecurityShip::removeWeapon(WeaponPlaces place)
{
    unsigned int indexOfWeapon = static_cast<unsigned int>(place);

    if (indexOfWeapon > 3)
    {
        return *this;
    }

    delete availableWeaponPlaces[indexOfWeapon];
    availableWeaponPlaces[indexOfWeapon] = nullptr;

    return *this;
}

int SecurityShip::shootToPoint(const Point& point) const
{
    size_t n = availableWeaponPlaces.size();
    int wholeDamage = 0;

    for (size_t i = 0; i < n; i++)
    {
        Weapon* currentWeapon = availableWeaponPlaces[i];
        int damageOfCurrentWeapon = 0;

        if (currentWeapon != nullptr && currentWeapon->getFireRange() >= distanceBetweenTwoPoints(point, coordinatesOfShip) )
        {
            damageOfCurrentWeapon = currentWeapon->shoot();
        }
        else
        {
            damageOfCurrentWeapon = 0;
        }

        wholeDamage += damageOfCurrentWeapon;
    }

    return wholeDamage;
}

SecurityShip::~SecurityShip()
{
    for (size_t i = 0; i < COUNT_OF_PLACES; ++i)
    {
        delete availableWeaponPlaces[i];
    }
}




TransportShip& TransportShip::setWeight(int weight)
{
    if (weight > maxWeight)
    {
        throw std::logic_error("Weight can't be more than max weight");
    }

    currentWeight = weight;
    calculateMaxVelocity();
    
    return *this;
}


TransportShip& TransportShip::calculateMaxVelocity()
{
    ratio = (maxWeight + currentWeight) / maxWeight;
    maxVelocity /= ratio;
    return *this;
}





const Weapon* BattleTransport::getWeaponInfo(WeaponPlaces place_) const
{
    unsigned int indexOfWeapon = static_cast<unsigned int>(place_);

    if (indexOfWeapon > 3)
    {
        return nullptr;
    }

    return availableWeaponPlaces[indexOfWeapon];
}


BattleTransport& BattleTransport::addWeapon(WeaponPlaces place_, Weapon* weapon_)
{
    int indexOfWeapon = static_cast<int>(place_);

    if (indexOfWeapon > 3)
    {
        return *this;
    }

    availableWeaponPlaces[indexOfWeapon] = weapon_;
    return *this;
}


BattleTransport& BattleTransport::removeWeapon(WeaponPlaces place_)
{
    unsigned int indexOfWeapon = static_cast<unsigned int>(place_);

    if (indexOfWeapon > 3)
    {
        return *this;
    }

    delete availableWeaponPlaces[indexOfWeapon];
    availableWeaponPlaces[indexOfWeapon] = nullptr;

    return *this;
}


int BattleTransport::shootToPoint(const Point& point) const
{
    size_t n = availableWeaponPlaces.size();
    int wholeDamage = 0;

    for (size_t i = 0; i < n; i++)
    {
        Weapon* currentWeapon = availableWeaponPlaces[i];
        int damageOfCurrentWeapon = 0;

        if (currentWeapon != nullptr && currentWeapon->getFireRange() >= distanceBetweenTwoPoints(point, coordinatesOfShip))
        {
            damageOfCurrentWeapon = currentWeapon->shoot();
        }
        else
        {
            damageOfCurrentWeapon = 0;
        }

        wholeDamage += damageOfCurrentWeapon;
    }

    return wholeDamage;
}

BattleTransport::~BattleTransport()
{
    for (size_t i = 0; i < COUNT_OF_PLACES; ++i)
    {
        delete availableWeaponPlaces[i];
    }
}
