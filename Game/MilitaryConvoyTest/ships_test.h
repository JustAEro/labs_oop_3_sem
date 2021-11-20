/// @cond

#include <gtest/gtest.h>
#include "../MilitaryConvoy/Ships/Ship.h"


TEST(SecurityShipDefaultConstructor, TestSecurityShip)
{
	Ship* s = new SecurityShip;
	
	ASSERT_EQ(s->getCoordinates(), Point(0, 0));
	ASSERT_EQ(SecurityShip::DEFAULT_MAX_VELOCITY, s->getMaxVelocity());
	delete s;
}

TEST(BattleTransportDefaultConstructor, TestBattleTransport)
{
	
	Ship* bt = new BattleTransport;
	ASSERT_EQ(ShipTypes::BattleTransport, bt->getType());
	
	BattleTransport* bt_ptr = static_cast<BattleTransport*>(bt);
	ASSERT_EQ(bt_ptr->getWeaponInfo(BattleTransport::WeaponPlaces::Stern), nullptr);
	ASSERT_EQ(bt_ptr->getWeaponInfo(BattleTransport::WeaponPlaces::Nose), nullptr);

	delete bt;
}

TEST(SecurityShipTest, SecurityShipTest)
{
	SecurityShip* sec_ship = new SecurityShip( Captain("Fedor", CaptainRanks::Second), Point(1, 2) );

	sec_ship->addWeapon(SecurityShip::WeaponPlaces::Stern, new Weapon(WeaponTypes::Heavy));

	ASSERT_EQ(sec_ship->getWeaponInfo(SecurityShip::WeaponPlaces::Stern)->getType(), WeaponTypes::Heavy);

	delete sec_ship;
}

TEST(BattleTransportTest, BattleTransportTest)
{
	BattleTransport* bat_trans = new BattleTransport( Captain("Egor", CaptainRanks::Third), Point(2, 8) );

	bat_trans->addWeapon(BattleTransport::WeaponPlaces::LeftSide, new Weapon(WeaponTypes::Medium));

	ASSERT_EQ(bat_trans->getWeaponInfo(BattleTransport::WeaponPlaces::LeftSide)->getType(), WeaponTypes::Medium);
	ASSERT_EQ(bat_trans->getWeaponInfo(BattleTransport::WeaponPlaces::Nose), nullptr);

	delete bat_trans;
}



/// @endcond