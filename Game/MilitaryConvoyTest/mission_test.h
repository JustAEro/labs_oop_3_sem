/// @cond

#pragma once

#include <gtest/gtest.h>
#include <vector>
#include "../MilitaryConvoy/Mission/Mission.h"


TEST(MissionTest, MissionTest)
{
	Mission mission;

	int count = 10;
	std::vector<int> IDs(count);
	for (int i = 0; i < count; ++i)
	{
		IDs[i] = mission.createBattlePirateShip();
		ASSERT_EQ(IDs[i], i);
	}
	
	ASSERT_EQ(mission.getTablePirates().getCountOfShips(), count);


	const Table& tab_pirates = mission.getTablePirates();
	for (Table::const_iterator it = tab_pirates.cbegin(); it != tab_pirates.cend(); ++it)
	{
		ASSERT_EQ((*it).second->getType(), ShipTypes::SecurityShip);
		SecurityShip* cur_ship = static_cast<SecurityShip*>( (*it).second );
	}

}


/// @endcond