/// @cond
#pragma once

#include <gtest/gtest.h>
#include "../MilitaryConvoy/Table/TableElement.h"



TEST(TableTest, TestTable) 
{
	Table tab;
	ASSERT_TRUE(tab.getShipByID(100) == nullptr);

	Ship* s_bt = new BattleTransport;
	int id = tab.addShip(s_bt);

	ASSERT_EQ(1, tab.getCountOfShips());
	ASSERT_EQ(s_bt, tab.getShipByID(id));

	Ship* sh = tab.getShipByID(id);
	ASSERT_EQ(sh->getType(), ShipTypes::BattleTransport);
	
	BattleTransport* bt = static_cast<BattleTransport*>(sh);
	bt->addWeapon(BattleTransport::WeaponPlaces::Stern, new Weapon(WeaponTypes::Heavy));
	bt->addWeapon(BattleTransport::WeaponPlaces::Nose, new Weapon(WeaponTypes::Medium));

	
	bt->removeWeapon(BattleTransport::WeaponPlaces::Stern);
	
	ASSERT_EQ(0, tab.removeShip(id));  //ok
	ASSERT_EQ(0, tab.getCountOfShips());
	ASSERT_EQ(-1, tab.removeShip(id));  //not found
}



/// @endcond