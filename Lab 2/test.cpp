#include "pch.h"
#include "..\Library\Hypocycloid.h"
#include "gtest/gtest.h"
#include "tchar.h"

/*
TEST(TestCaseName, TestName) 
{
	EXPECT_EQ(1, 1); 
	EXPECT_TRUE(true);
}
*/

TEST(HypocicloidConstructor, DefaultConstructor)
{
	Prog2::Hypocycloid hp;
	ASSERT_EQ(2.0, hp.getR1());
	ASSERT_EQ(1.0, hp.getR2());
	ASSERT_EQ(0, hp.getC1().x);
	ASSERT_EQ(0, hp.getC1().y);
	ASSERT_EQ(1, hp.getC2().x);
	ASSERT_EQ(0, hp.getC2().y);
	ASSERT_EQ(2, hp.getRollingPoint().x);
	ASSERT_EQ(0, hp.getRollingPoint().y);
}


int _tmain(int argc, _TCHAR* argv[]) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}