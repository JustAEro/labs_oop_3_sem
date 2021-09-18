#pragma once

#include <iostream>
#include "..\Library\Hypocycloid.h"


//functions to organize the dialog, if EOF they return -1 and if they work correctly they return 0

int	D_Hypocycloid_New(Hypocycloid*& hp),   //construct new hypocycloid

	D_Show_Full_Info(Hypocycloid*& hp),      //show full info about hypocycloid (big radius, small radius and distance)

	D_Set_Radius_Big(Hypocycloid*& hp),    //set big radius
	D_Set_Radius_Small(Hypocycloid*& hp),  //set small radius
	D_Set_Distance(Hypocycloid*& hp),		//set distance

	D_Get_Radius_Big(Hypocycloid*& hp),    //get big radius
	D_Get_Radius_Small(Hypocycloid*& hp),    //get small radius
	D_Get_Distance(Hypocycloid*& hp),    //get distance

	D_Point_Of_Angle(Hypocycloid*& hp),         //get point of parameter which is angle
	D_Curv_Radius_Of_Angle(Hypocycloid*& hp),	//get curve radius of parameter which is angle
	D_Sectorial_Area(Hypocycloid*& hp),			//get sectorial point of parameter which is angle
	D_All_Parameters_Of_Angle(Hypocycloid*& hp),	//get all functions of parameter which is angle

	D_Type(Hypocycloid*& hp),					//show type of hypocycloid

	D_Delete(Hypocycloid*& hp);					//delete hypocycloid



void start_menu(Hypocycloid*& hp);			//function to start menu in application program
	


int dialog(const char* msgs[], int);	//function to select the number of alternative



template <typename T> int get_T(T& x)		//get argument of T type from std::cin
{
	std::cin >> x;
	while (!std::cin.good())
	{
		if (std::cin.eof() || std::cin.bad())
		{
			return -1;   //eof or fatal error
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.clear();

		std::cout << "You are wrong! Please, repeat input from incorrect token.\n";
		std::cin >> x;

	}
	return 0;  //ok
}



	