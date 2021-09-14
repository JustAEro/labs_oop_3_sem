#include "pch.h"
#include "..\Library\Hypocycloid.h"
#include "gtest/gtest.h"
#include "tchar.h"

TEST(TestCaseName, TestName) 
{
	EXPECT_EQ(1, 1); 
	EXPECT_TRUE(true);
}


int _tmain(int argc, _TCHAR* argv[]) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}