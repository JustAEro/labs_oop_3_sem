#include <gtest/gtest.h>
#include "../Mission/Mission.h"

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
//-----includes for debugging memory leaks in VS-----/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//---------------------------------------------------/
#endif


TEST(MissionTest, MissionTest)
{
	Mission mission;
	mission.createBattlePirateShip();
	ASSERT_EQ(mission.getTablePirates().getCountOfShips(), 1);
}




int main(int argc, wchar_t* argv[])
{
	#if defined (_MSC_VER) && !defined (__INTEL_COMPILER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);   //flag to detect memory leaks in VS
	#endif

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
