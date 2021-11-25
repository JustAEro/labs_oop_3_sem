/// @cond
#pragma once

#include <gtest/gtest.h>
#include "../MilitaryConvoy/Weapons/Weapon.h"

TEST(DefaultConstructor, TestingDefaultConstructor)
{
	Weapon w;

	ASSERT_EQ(WeaponTypes::Light, w.getType());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_DAMAGE, w.getDamage());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_FIRE_RATE, w.getFireRate());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_MAX_AMMO, w.getCurrentAmmo());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_MAX_AMMO, w.getMaxAmmo());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_COST, w.getCost());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_FIRE_RANGE, w.getFireRange());
	ASSERT_EQ(false, w.getIsShooting());
}


TEST(TypeConstructor, TestingTypeConstructor)
{
	Weapon w_light(WeaponTypes::Light);

	ASSERT_EQ(WeaponTypes::Light, w_light.getType());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_DAMAGE, w_light.getDamage());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_FIRE_RATE, w_light.getFireRate());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_MAX_AMMO, w_light.getCurrentAmmo());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_MAX_AMMO, w_light.getMaxAmmo());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_COST, w_light.getCost());
	ASSERT_EQ(Weapon::DEFAULT_LIGHT_WEAPON_FIRE_RANGE, w_light.getFireRange());
	ASSERT_EQ(false, w_light.getIsShooting());



	Weapon w_medium(WeaponTypes::Medium);

	ASSERT_EQ(WeaponTypes::Medium, w_medium.getType());
	ASSERT_EQ(Weapon::DEFAULT_MEDIUM_WEAPON_DAMAGE, w_medium.getDamage());
	ASSERT_EQ(Weapon::DEFAULT_MEDIUM_WEAPON_FIRE_RATE, w_medium.getFireRate());
	ASSERT_EQ(Weapon::DEFAULT_MEDIUM_WEAPON_MAX_AMMO, w_medium.getCurrentAmmo());
	ASSERT_EQ(Weapon::DEFAULT_MEDIUM_WEAPON_MAX_AMMO, w_medium.getMaxAmmo());
	ASSERT_EQ(Weapon::DEFAULT_MEDIUM_WEAPON_COST, w_medium.getCost());
	ASSERT_EQ(Weapon::DEFAULT_MEDIUM_WEAPON_FIRE_RANGE, w_medium.getFireRange());
	ASSERT_EQ(false, w_medium.getIsShooting());


	Weapon w_heavy(WeaponTypes::Heavy);

	ASSERT_EQ(WeaponTypes::Heavy, w_heavy.getType());
	ASSERT_EQ(Weapon::DEFAULT_HEAVY_WEAPON_DAMAGE, w_heavy.getDamage());
	ASSERT_EQ(Weapon::DEFAULT_HEAVY_WEAPON_FIRE_RATE, w_heavy.getFireRate());
	ASSERT_EQ(Weapon::DEFAULT_HEAVY_WEAPON_MAX_AMMO, w_heavy.getCurrentAmmo());
	ASSERT_EQ(Weapon::DEFAULT_HEAVY_WEAPON_MAX_AMMO, w_heavy.getMaxAmmo());
	ASSERT_EQ(Weapon::DEFAULT_HEAVY_WEAPON_COST, w_heavy.getCost());
	ASSERT_EQ(Weapon::DEFAULT_HEAVY_WEAPON_FIRE_RANGE, w_heavy.getFireRange());
	ASSERT_EQ(false, w_heavy.getIsShooting());
}

TEST(TypeConstructor, TypeConstructorThrowsLogicError)
{
	ASSERT_THROW( Weapon{WeaponTypes::Count}, std::logic_error );
}

TEST(SetCurrentAmmo, SetCurrentAmmoThrowsLogicError)
{
	Weapon w_light(WeaponTypes::Light);

	ASSERT_THROW(w_light.setCurrentAmmo(Weapon::DEFAULT_LIGHT_WEAPON_MAX_AMMO + 1), std::logic_error);
}


/// @endcond