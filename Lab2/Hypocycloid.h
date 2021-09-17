#pragma once


const double eps = 10e-5;

struct Point
{
	double x;
	double y;
};

class Hypocycloid
{
public:
	Hypocycloid();
	Hypocycloid(double radBig, double radSmall = 1.0, double dist = 1.0);

	//setters
	Hypocycloid& setRadiusBig(double r);
	Hypocycloid& setRadiusSmall(double r);
	Hypocycloid& setDistance(double dist);
		
	//getters
	double getRadiusBig() const { return radiusBig; }
	double getRadiusSmall() const { return radiusSmall; }
	double getDistance() const { return distance; }

	//other methods
	Point pointOfAngle(double t) const;
	double curvRadiusOfAngle(double t) const;
	double sectorialArea(double t) const;

	enum class Types
	{
		SIMPLE,
		LONG,
		SHORT
	};

	Types type() const;

		

private:
	double radiusBig;   //big circle
	double radiusSmall;   //small circle
	double distance;   //distance from center of small circle to rolling point
};


