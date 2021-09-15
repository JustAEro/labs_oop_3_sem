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
	Hypocycloid hp;
	ASSERT_EQ(2.0, hp.getRadiusBig());
	ASSERT_EQ(1.0, hp.getRadiusSmall());
	ASSERT_EQ(1.0, hp.getDistance());
}

TEST(HypocicloidConstructor, InitConstructor)
{
	Hypocycloid hp(5, 4, 4);

	ASSERT_EQ(5, hp.getRadiusBig());
	ASSERT_EQ(4, hp.getRadiusSmall());
	ASSERT_EQ(4, hp.getDistance());
}


TEST(HypocicloidConstructor, TestException)
{
	ASSERT_ANY_THROW(Hypocycloid(1, 2, 5));
	ASSERT_ANY_THROW(Hypocycloid(-1, 4, 4));
	ASSERT_ANY_THROW(Hypocycloid(1, -4, 4));
	ASSERT_ANY_THROW(Hypocycloid(1, 4, -4));
}


TEST(HypocicloidMethods, Setters)
{
	Hypocycloid hp;

	ASSERT_ANY_THROW(hp.setRadiusBig(1));
	ASSERT_ANY_THROW(hp.setRadiusSmall(2.5));

	hp.setDistance(3);
	ASSERT_EQ(3, hp.getDistance());

	hp.setRadiusBig(5);
	ASSERT_EQ(5, hp.getRadiusBig());

	hp.setRadiusSmall(3);
	ASSERT_EQ(3, hp.getRadiusSmall());

	ASSERT_ANY_THROW(hp.setDistance(-2));
	ASSERT_ANY_THROW(hp.setRadiusBig(-2));
	ASSERT_ANY_THROW(hp.setRadiusSmall(-2));
}

TEST(HypocicloidMethods, ParametersDefault)
{
	Hypocycloid hp;

	ASSERT_NEAR(0, hp.sectorialArea(0.5), eps);
	ASSERT_NEAR(0, hp.sectorialArea(-1), eps);
	ASSERT_NEAR(0, hp.sectorialArea(1), eps);
	ASSERT_EQ(Hypocycloid::Types::SIMPLE, hp.typeOfHypocycloid());

	hp.setDistance(2);
	ASSERT_EQ(Hypocycloid::Types::LONG, hp.typeOfHypocycloid());

	hp.setDistance(0.5);
	ASSERT_EQ(Hypocycloid::Types::SHORT, hp.typeOfHypocycloid());
}

TEST(HypocicloidMethods, Parameters)
{
	double rad1 = 3, rad2 = 2, dist = 2;

	Hypocycloid hp(rad1, rad2, dist);
	

	ASSERT_NEAR(-1.0116717, hp.pointOfAngle(6.5).x, eps);
	ASSERT_NEAR(0.431510, hp.pointOfAngle(6.5).y, eps);

	ASSERT_NEAR(7.21814, hp.curvRadiusOfAngle(1.5), eps);

	ASSERT_NEAR(-1.0093577, hp.sectorialArea(1.5), eps);
}

int _tmain(int argc, _TCHAR* argv[]) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}