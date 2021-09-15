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

TEST(HypocicloidConstructor, InitConstructor)
{
	Prog2::Point p1 = { 5, 6 }, p2 = { 4, 6 }, p3 = { 0, 0 };
	Prog2::Hypocycloid hp(p1, p2, p3, 5, 4);

	ASSERT_EQ(5, hp.getC1().x);
	ASSERT_EQ(6, hp.getC1().y);
	ASSERT_EQ(4, hp.getC2().x);
	ASSERT_EQ(6, hp.getC2().y);
	ASSERT_EQ(0, hp.getRollingPoint().x);
	ASSERT_EQ(0, hp.getRollingPoint().y);
	ASSERT_EQ(5, hp.getR1());
	ASSERT_EQ(4, hp.getR2());
}


TEST(HypocicloidConstructor, TestException)
{
	Prog2::Point p1 = { 0,0 }, p2 = { 0,0 }, p3 = {0,0};
	ASSERT_ANY_THROW(Prog2::Hypocycloid(p1, p2, p3, -1, 1));
	ASSERT_ANY_THROW(Prog2::Hypocycloid(p1, p2, p3));
	ASSERT_ANY_THROW(Prog2::Hypocycloid(p1, p2, p3, 1, -1));
	ASSERT_ANY_THROW(Prog2::Hypocycloid(p1, p2, p3, 1, 2));
	ASSERT_ANY_THROW(Prog2::Hypocycloid(p1, p2, p3, 3, 2));
	ASSERT_ANY_THROW(Prog2::Hypocycloid(p1, p2, p3, 2, 2));

	p1 = { 5,6 };
	p2 = { 4,5 };
	ASSERT_ANY_THROW(Prog2::Hypocycloid(p1, p2, p3, 5, 2));
}


TEST(HypocicloidMethods, Setters)
{
	Prog2::Hypocycloid hp;
	Prog2::Point p1 = {1, 2};
	ASSERT_ANY_THROW(hp.setC1(p1));
	ASSERT_ANY_THROW(hp.setC2(p1));

	Prog2::Point p2 = { 1, 1 };
	ASSERT_ANY_THROW(hp.setC2(p2));

	hp.setC1C2(p1, p2);
	ASSERT_EQ(1, hp.getC1().x);
	ASSERT_EQ(2, hp.getC1().y);
	ASSERT_EQ(1, hp.getC2().x);
	ASSERT_EQ(1, hp.getC2().y);


	hp.setRollingPoint(p1);
	ASSERT_EQ(1, hp.getRollingPoint().x);
	ASSERT_EQ(2, hp.getRollingPoint().y);
	
	p2 = { -1, 0 };
	ASSERT_ANY_THROW(hp.setC1C2(p1, p2));

	
	hp.setR1R2(3, 2);
	ASSERT_EQ(3, hp.getR1());
	ASSERT_EQ(2, hp.getR2());

	ASSERT_ANY_THROW(hp.setR1R2(4, 2));

	double rad1 = 4;
	double rad2 = 3;
	p1 = {7, 8} ;
	p2 = {6, 8};
	hp.setR1R2C1C2(rad1, rad2, p1, p2);
	ASSERT_EQ(4, hp.getR1());
	ASSERT_EQ(3, hp.getR2());
	ASSERT_EQ(7, hp.getC1().x);
	ASSERT_EQ(8, hp.getC1().y);
	ASSERT_EQ(6, hp.getC2().x);
	ASSERT_EQ(8, hp.getC2().y);

	p2 = { 6, 7 };
	ASSERT_ANY_THROW(hp.setR1R2C1C2(rad1, rad2, p1, p2));
}

TEST(HypocicloidMethods, ParametersDefault)
{
	Prog2::Hypocycloid hp;

	ASSERT_NEAR(0, hp.sectorialArea(0.5), Prog2::eps);
	ASSERT_NEAR(0, hp.sectorialArea(-1), Prog2::eps);
	ASSERT_NEAR(0, hp.sectorialArea(1), Prog2::eps);
	ASSERT_EQ(Prog2::Hypocycloid::SIMPLE, hp.typeOfHypocycloid());

	Prog2::Point p3 = { 3, 0 };
	hp.setRollingPoint(p3);
	ASSERT_EQ(Prog2::Hypocycloid::LONG, hp.typeOfHypocycloid());

	p3 = { -1, 0 };
	hp.setRollingPoint(p3);
	ASSERT_EQ(Prog2::Hypocycloid::LONG, hp.typeOfHypocycloid());

	p3 = { 1, 0 };
	hp.setRollingPoint(p3);
	ASSERT_EQ(Prog2::Hypocycloid::SHORT, hp.typeOfHypocycloid());
}

TEST(HypocicloidMethods, Parameters)
{
	double rad1 = 3, rad2 = 2;
	Prog2::Point p1 = {7, 0}, p2 = {8, 0}, p3 = {10, 0};
	Prog2::Hypocycloid hp(p1, p2, p3, rad1, rad2);
	

	ASSERT_NEAR(-1.0116717, hp.pointOfAngle(6.5).x, Prog2::eps);
	ASSERT_NEAR(0.431510, hp.pointOfAngle(6.5).y, Prog2::eps);

	ASSERT_NEAR(7.21814, hp.curvRadiusOfAngle(1.5), Prog2::eps);

	ASSERT_NEAR(-1.0093577, hp.sectorialArea(1.5), Prog2::eps);
}

int _tmain(int argc, _TCHAR* argv[]) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}