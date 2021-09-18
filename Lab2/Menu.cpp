#include "Menu.h"

int D_Hypocycloid_New(Hypocycloid*& hp)
{
	std::cout << "Enter new Hypocycloid. The old one will be deleted." << std::endl;

	double rad1, rad2, dist;

	int status;

	std::cout << "Enter radius of new big circle: ";
	status = get_T(rad1);

	if (status == -1)
	{
		return -1; //eof
	}


	std::cout << "Enter radius of new small circle: ";
	status = get_T(rad2);

	if (status == -1)
	{
		return -1; //eof
	}


	std::cout << "Enter distance from center of small circle to rolling point: ";
	status = get_T(dist);

	if (status == -1)
	{
		return -1; //eof
	}


	Hypocycloid* hp_new = nullptr;

	try
	{
		hp_new = new Hypocycloid(rad1, rad2, dist);     //check if new hypocycloid with this configuration exists
	}

	catch (std::exception& ex) 
	{
		std::cout << ex.what() << std::endl;
		std::cout << "Hypocycloid with this configuration doesn't exist! The previous hypocycloid is saved!" << std::endl;
		delete hp_new;   //if new hypocycloid with this configuration doesn't exist we delete it, save old hypocycloid and exit from function
		return 0;
	}

	
	delete hp;     //if new hypocycloid with this configuration exists we delete the old one and set new configuration
	hp = hp_new;
	
	return 0;
}

int D_Delete(Hypocycloid*& hp)
{
	std::cout << "Delete current Hypocycloid." << std::endl;

	delete hp;
	hp = nullptr;
	
	return 0;
}


int D_Type(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}

	std::cout << "The type of your hypocicloid is: ";
	Hypocycloid::Types type = hp->type();

	if (type == Hypocycloid::Types::SIMPLE)
	{
		std::cout << "simple" << std::endl;
	}
	else if (type == Hypocycloid::Types::LONG)
	{
		std::cout << "long" << std::endl;
	}
	else
	{
		std::cout << "short" << std::endl;
	}

	return 0;
}

int D_Sectorial_Area(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}

	int status;
	double t;
	std::cout << "Enter the angle to count sectorial area: ";
	status = get_T(t);

	if (status == -1)
	{
		return -1; //eof
	}

	std::cout << "Sectorial area of t: " << hp->sectorialArea(t) << std::endl;
	return 0;
}


int D_Curv_Radius_Of_Angle(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}

	int status;
	double t;
	std::cout << "Enter the angle to count curve radius: ";
	status = get_T(t);

	if (status == -1)
	{
		return -1; //eof
	}

	std::cout << "Curve radius of t: " << hp->curvRadiusOfAngle(t) << std::endl;
	return 0;
}


int D_Point_Of_Angle(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}

	int status;
	double t;
	std::cout << "Enter the angle to count point of angle: ";
	status = get_T(t);

	if (status == -1)
	{
		return -1; //eof
	}

	Point res = hp->pointOfAngle(t);

	std::cout << "Point of angle is: " << "{" << res.x << " , " << res.y <<"}" << std::endl;
	return 0;
}

int D_All_Parameters_Of_Angle(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}

	int status;
	double t;
	std::cout << "Enter the angle to count all parametres of angle: ";
	status = get_T(t);

	if (status == -1)
	{
		return -1; //eof
	}

	std::cout << "Curve radius of t: " << hp->curvRadiusOfAngle(t) << std::endl;

	Point res = hp->pointOfAngle(t);
	std::cout << "Hypocycloid point of t: " << "{" << res.x << " , " << res.y << "}" << std::endl;
	std::cout << "Sectorial area of t: " << hp->sectorialArea(t) << std::endl;
	return 0;
}

int D_Get_Distance(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}

	std::cout << "Distance from center of small circle to rolling point: " << hp->getDistance() << std::endl;
	return 0;
}

int D_Get_Radius_Small(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}

	std::cout << "Radius of small circle: " << hp->getRadiusSmall() << std::endl;
	return 0;
}

int D_Get_Radius_Big(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}
	std::cout << "Radius of big circle: " << hp->getRadiusBig() << std::endl;
	return 0;
}


int D_Set_Distance(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}

	int status;
	double dist;
	std::cout << "Enter the distance to set: ";
	status = get_T(dist);

	if (status == -1)
	{
		return -1; //eof
	}

	try
	{
		hp->setDistance(dist);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << "Hypocycloid with this configuration doesn't exist! The previous hypocycloid is saved!" << std::endl;
	}
	return 0;
}


int D_Set_Radius_Small(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}

	int status;
	double rad2;
	std::cout << "Enter the small radius to set: ";
	status = get_T(rad2);

	if (status == -1)
	{
		return -1; //eof
	}

	try
	{
		hp->setRadiusSmall(rad2);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << "Hypocycloid with this configuration doesn't exist! The previous hypocycloid is saved!" << std::endl;
	}
	return 0;
}


int D_Set_Radius_Big(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}

	int status;
	double rad1;
	std::cout << "Enter the big radius to set:  ";
	status = get_T(rad1);

	if (status == -1)
	{
		return -1; //eof
	}

	try
	{
		hp->setRadiusBig(rad1);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << "Hypocycloid with this configuration doesn't exist! The previous hypocycloid is saved!" << std::endl;
	}
	return 0;
}

int D_Show_Full_Info(Hypocycloid*& hp)
{
	if (hp == nullptr)
	{
		std::cout << "The Hypocycloid is empty! Create new one to operate with it!" << std::endl;
		return 0;
	}
	D_Get_Radius_Big(hp);
	D_Get_Radius_Small(hp);
	D_Get_Distance(hp);
	return 0;
}


int dialog(const char* msgs[], int size)
{
	const char* errmsg = "";
	int number_of_altenative;
	

	do {
		std::cout << errmsg << std::endl;
		errmsg = "You are wrong. Repeat, please!";

		//print the list of alternatives
		std::cout << "Choose the number from alternatives or press 0 or Ctrl+Z to quit" << std::endl << std::endl;
		for (int i = 0; i < size; ++i) 
		{
			std::cout << msgs[i] << std::endl;
		}

		std::cout << std::endl;
		std::cout << "Make your choice:  --> " << std::endl;

		int n = get_T(number_of_altenative); //input the number of alternative
		if (n == -1) {
			number_of_altenative = 0;
		}
	} while (number_of_altenative < 0 || number_of_altenative >= size);

	return number_of_altenative;
}


void start_menu(Hypocycloid*& hp)
{
	int (*dialog_functions[])(Hypocycloid * &hp) = { nullptr,	D_Hypocycloid_New,
												D_Show_Full_Info,

												D_Set_Radius_Big,    //set big radius
												D_Set_Radius_Small,  //set small radius
												D_Set_Distance,		//set distance

												D_Get_Radius_Big,    //get big radius
												D_Get_Radius_Small,    //get small radius
												D_Get_Distance,    //get distance

												D_Point_Of_Angle,
												D_Curv_Radius_Of_Angle,
												D_Sectorial_Area,
												D_All_Parameters_Of_Angle,

												D_Type,

												D_Delete,
										};


	//Alternatives for a dialog
	//the list of alternatives
	const char* msgs[] = { "0. Quit",   "1. New Hypocycloid", "2. Show full info" ,

										"3. Set Big Radius", "4. Set Small Radius", "5. Set Distance",

										"6. Get Big Radius", "7. Get Small Radius", "8. Get Distance",

										"9. Point of angle", "10. Curve radius of angle", "11. Sectorial area of angle",
										
										"12. All parameters from points 9-11 of angle",

										"13. Type of Hypocycloid" , "14. Delete Hypocycloid",
										
										
						 };

	//the number of alternatives
	const int menu_size = sizeof(msgs) / sizeof(msgs[0]);

	int number_of_alternative;
	while ((number_of_alternative = dialog(msgs, menu_size)))
	{
		if (dialog_functions[number_of_alternative](hp) == -1)
		{
			break;
		}
	}

	printf("That's all. Bye!\n");

}