#include <gtest/gtest.h>
#include "../Table/TableElement.h"

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
//-----includes for debugging memory leaks in VS-----/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------------------------------------/
#endif


TEST(TestTable, TestTable) 
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


int main(int argc, wchar_t* argv[])
{
	#if defined (_MSC_VER) && !defined (__INTEL_COMPILER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);   //flag to detect memory leaks in VS
	#endif

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
