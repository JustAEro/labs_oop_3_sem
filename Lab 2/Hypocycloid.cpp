#include "pch.h"

#include <iostream>
#include <cmath>
//#include <stdexcept>

#include "Hypocycloid.h"

namespace Prog2 
{
	Hypocycloid::Hypocycloid()
	{
		r1 = 2.0;
		r2 = 1.0;

		c1 = { 0, 0 };
		c2 = { 1, 0 };

		rollingPoint = { 2, 0 };

	}

	Hypocycloid::Hypocycloid(const Point& p1, const Point& p2, const Point& roll, double rad1, double rad2)
	{
		if (rad1 < 0)
		{
			throw std::exception("invalid radius 1");
		}
		r1 = rad1;

		if (rad2 < 0)
		{
			throw std::exception("invalid radius 2");
		}
		r2 = rad2;

		if ( !checkInternalTouch(rad1, rad2, p1, p2) )
		{
			throw std::exception("no internal touch");
		}
		c1 = p1;
		c2 = p2;

		rollingPoint = roll;
	}

	Hypocycloid& Hypocycloid::setR1(double r)
	{
		if (r < 0) 
		{
			throw std::exception("invalid radius 1");
		}

		if (!checkInternalTouch(r, r2, c1, c2))
		{
			throw std::exception("no internal touch");
		}

		r1 = r;
		return *this;
	}


	Hypocycloid& Hypocycloid::setR2(double r)
	{
		if (r < 0)
		{
			throw std::exception("invalid radius 2");
		}

		if (!checkInternalTouch(r1, r, c1, c2))
		{
			throw std::exception("no internal touch");
		}

		r2 = r;
		return *this;
	}

	Hypocycloid& Hypocycloid::setC1(const Point& p1)
	{
		if (!checkInternalTouch(r1, r2, p1, c2))
		{
			throw std::exception("no internal touch");
		}
		c1 = p1; 
		return *this; 
	}


	Hypocycloid& Hypocycloid::setC2(const Point& p2)
	{
		if (!checkInternalTouch(r1, r2, c1, p2))
		{
			throw std::exception("no internal touch");
		}
		c2 = p2;
		return *this;
	}
	

	Point Hypocycloid::pointOfAngle(double t) const
	{
		double d = dist(rollingPoint, c2);
		double x = (r1 - r2) * cos(t) + d * cos((r1 - r2) *t / r2);
		double y = (r1 - r2) * sin(t) - d * sin((r1 - r2) * t / r2);

		Point res = { x, y };
		return res;
	}

	double Hypocycloid::curvRadiusOfAngle(double t) const
	{
		double d = dist(rollingPoint, c2);

		double a = pow( (r2*r2 + d*d - 2*d*r2*cos(r1*t/r2)), 1.5);
		double b = abs( (-1)*r2*r2*r2 + d*d*(r1-r2) - d*r2*(r1-2*r2) * cos(r1*t/r2) );

		double res = (r1-r2) * a / b;
		return res;
	}

	double Hypocycloid::sectorialArea(double t) const
	{
		double d = dist(rollingPoint, c2);
		double s = (r1 - r2) * ( (r1-r2-(d*d)/r2)*t + d*(r1-2*r2)*sin(r1*t/r2)/r1 ) / 2;
		return s;
	}


	int Hypocycloid::typeOfHypocycloid() const 
	{
		double d = dist(rollingPoint, c2);
		//double eps = 10e-5;

		if (abs(d - r2) < eps)
		{
			return SIMPLE; //simple
		}

		if (d > r2)
		{
			return LONG; //long
		}

		return SHORT; //short
	}


}