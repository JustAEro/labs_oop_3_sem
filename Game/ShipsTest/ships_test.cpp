#include <gtest/gtest.h>
#include "Ship.h"

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
//-----includes for debugging memory leaks in VS-----/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------------------------------------/
#endif

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



int main(int argc, wchar_t* argv[])
{
	#if defined (_MSC_VER) && !defined (__INTEL_COMPILER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);   //flag to detect memory leaks in VS
	#endif

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
