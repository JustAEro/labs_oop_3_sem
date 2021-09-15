#include "pch.h"

#include <iostream>
#include <cmath>
//#include <stdexcept>

#include "Hypocycloid.h"



Hypocycloid::Hypocycloid()
{
	radiusBig = 2.0;
	radiusSmall = 1.0;
	distance = 1.0;
}

Hypocycloid::Hypocycloid(double radBig, double radSmall, double dist)
{
	if (radBig <= 0)
	{
		throw std::exception("Invalid big radius");
	}
	if (radSmall <= 0)
	{
		throw std::exception("Invalid small radius");
	}

	if (radBig <= radSmall)
	{
		throw std::exception("Big radius can't be smaller of equal than small radius");
	}

	if (dist <= 0) 
	{
		throw std::exception("Invalid distance");
	}
	radiusBig = radBig;
	radiusSmall = radSmall;
	distance = dist;
}



Hypocycloid& Hypocycloid::setRadiusBig(double r)
{
	if (r <= 0)
	{
		throw std::exception("Invalid radius big");
	}

	if (r <= radiusSmall)
	{
		throw std::exception("Big radius can't be smaller of equal than small radius");
	}

	radiusBig = r;
	return *this;
}

Hypocycloid& Hypocycloid::setRadiusSmall(double r)
{
	if (r <= 0)
	{
		throw std::exception("Invalid radius small");
	}

	if (r >= radiusBig)
	{
		throw std::exception("Small radius can't be bigger of equal than big radius");
	}

	radiusSmall = r;
	return *this;
}

Hypocycloid& Hypocycloid::setDistance(double dist)
{
	if (dist <= 0)
	{
		throw std::exception("Invalid distance");
	}

	distance = dist;
	return *this;
}

	

Point Hypocycloid::pointOfAngle(double t) const
{
	double d = distance;
	double r1 = radiusBig;
	double r2 = radiusSmall;
	double x = (r1 - r2) * cos(t) + d * cos((r1 - r2) *t / r2);
	double y = (r1 - r2) * sin(t) - d * sin((r1 - r2) * t / r2);

	Point res = { x, y };
	return res;
}

double Hypocycloid::curvRadiusOfAngle(double t) const
{
	double d = distance;
	double r1 = radiusBig;
	double r2 = radiusSmall;

	double a = pow( (r2*r2 + d*d - 2*d*r2*cos(r1*t/r2)), 1.5);
	double b = abs( (-1)*r2*r2*r2 + d*d*(r1-r2) - d*r2*(r1-2*r2) * cos(r1*t/r2) );

	double res = (r1-r2) * a / b;
	return res;
}

double Hypocycloid::sectorialArea(double t) const
{
	double d = distance;
	double r1 = radiusBig;
	double r2 = radiusSmall;

	double s = (r1 - r2) * ( (r1-r2-(d*d)/r2)*t + d*(r1-2*r2)*sin(r1*t/r2)/r1 ) / 2;
	return s;
}


Hypocycloid::Types Hypocycloid::typeOfHypocycloid() const 
{
	
	if (abs(distance - radiusSmall) < eps)
	{
		return Types::SIMPLE; //simple
	}

	if (distance > radiusSmall)
	{
		return Types::LONG; //long
	}

	return Types::SHORT; //short
}


