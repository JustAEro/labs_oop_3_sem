#pragma once
#include <iostream>
#include <random>
#include <string>
#include "DynSet.h"
#include "SetTheoryProblems.h"


//functions to organize the dialog, if EOF they return -1 and if they work correctly they return 0

int	D_Problems_New(SetTheoryProblems&);   //construct problems for new sets
int D_Log_In_Teacher(SetTheoryProblems&);      //log in to the teacher's profile
int D_Log_Out_Teacher(SetTheoryProblems&);  //log out of the teacher's profile
int D_Show_Answers(SetTheoryProblems&);     //show answers for problems



void start_menu(SetTheoryProblems&);			//function to start menu in application program



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
		//ignore incorrect input until the end of the stream or until the end of the line and clear flag of errors


		std::cout << "You are wrong! Please, repeat input from incorrect token.\n";
		std::cin >> x;

	}
	return 0;  //ok
}



int randInt(unsigned int);