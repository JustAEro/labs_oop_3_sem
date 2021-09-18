#pragma once

const double eps = 1e-5;   //error for calculations in double (now it's 0.00001)

struct Point		//struct to store a point
{
	double x;		//x coordinate
	double y;		//y coordinate
};

class Hypocycloid
{
public:
	Hypocycloid();		//empty constructor for hypocycloid 
	Hypocycloid(double radBig, double radSmall = 1.0, double dist = 1.0);   //initializing constructor for hypocycloid

	//setters
	Hypocycloid& setRadiusBig(double r);			//setter for radius of big circle of hypocycloid 
	Hypocycloid& setRadiusSmall(double r);			//setter for radius of small circle of hypocycloid
	Hypocycloid& setDistance(double dist);			//setter for distance from center of small circle to rolling point
		
	//getters
	double getRadiusBig() const { return radiusBig; }				//getter for radius of big circle of hypocycloid 
	double getRadiusSmall() const { return radiusSmall; }			//getter for radius of small circle of hypocycloid
	double getDistance() const { return distance; }					//getter for distance from center of small circle to rolling point

	//other methods
	Point pointOfAngle(double t) const;					//method to calculate point of parameter which is angle
	double curvRadiusOfAngle(double t) const;			//method to calculate curve radius of parameter which is angle
	double sectorialArea(double t) const;				//method to calculate sectorial area of parameter which is angle
		

	enum class Types			//enum for 3 different types of Hypocycloid
	{
		SIMPLE,
		LONG,
		SHORT
	};

	Types type() const;			//method to calculate type of Hypocycloid

		

private:
	double radiusBig;   //radius of big circle
	double radiusSmall;   //radius of small circle
	double distance;   //distance from center of small circle to rolling point
};


