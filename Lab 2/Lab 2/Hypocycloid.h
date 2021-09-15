#pragma once

namespace Prog2 
{

	const double eps = 10e-5;

	struct Point
	{
		double x;
		double y;
	};

	double dist(const Point& a, const Point& b);   //distance between 2 points

	bool checkInternalTouch(double rad1, double rad2, const Point& p1, const Point& p2);

	class Hypocycloid
	{
	public:
		Hypocycloid();
		Hypocycloid(const Point& p1, const Point& p2, const Point& roll, double rad1 = 2.0, double rad2 = 1.0);

		//setters
		Hypocycloid& setR1(double r);
		Hypocycloid& setR2(double r);
		Hypocycloid& setR1R2(double rad1, double rad2);
		Hypocycloid& setC1(const Point& p1);
		Hypocycloid& setC2(const Point& p2);
		Hypocycloid& setC1C2(const Point& p1, const Point& p2);
		Hypocycloid& setR1R2C1C2(double rad1, double rad2, const Point& p1, const Point& p2);
		Hypocycloid& setRollingPoint(const Point& p) { rollingPoint = p; return *this; }

		//getters
		double getR1() const { return r1; }
		double getR2() const { return r2; }
		Point getC1() const { return c1; }
		Point getC2() const { return c2; }
		Point getRollingPoint() const { return rollingPoint; }
		
		//other methods
		Point pointOfAngle(double t) const;
		double curvRadiusOfAngle(double t) const;
		double sectorialArea(double t) const;
		int typeOfHypocycloid() const;

		enum Types
		{
			SIMPLE,
			LONG,
			SHORT
		};

	private:
		double r1;   //big circle
		Point c1;	//center of big circle

		double r2;   //small circle
		Point c2;	//center of small circle

		Point rollingPoint;   //rolling point
	};

}
