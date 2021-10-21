#pragma once

#if defined(_WIN32)
#include <Windows.h>
#define NOMINMAX
#endif

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "DynSet.h"
#include "SetTheoryProblems.h"


//functions to organize the dialog, if EOF they return -1 and if they work correctly they return 0

int	D_Problems_New(SetTheoryProblems&);   //construct problems for new sets
int D_Log_In_Teacher(SetTheoryProblems&);      //log in to the teacher's profile
int D_Log_Out_Teacher(SetTheoryProblems&);  //log out of the teacher's profile
int D_Show_Answers(SetTheoryProblems&);     //show answers for problems
int D_Solve_Problem_Union(SetTheoryProblems&);  //solve problem with union of 2 sets
int D_Solve_Problem_Intersection(SetTheoryProblems&);  //solve problem with intersection of 2 sets
int D_Solve_Problem_Difference(SetTheoryProblems&);  //solve problem with difference of 2 sets
int D_Solve_Problem_Symmetric_Difference(SetTheoryProblems&); //solve problem with symmetric difference of 2 sets
int D_Set_A(SetTheoryProblems&);   //initialize Set A with new int values
int D_Set_B(SetTheoryProblems&);   //initialize Set B with new int values
int D_Print_Sets(SetTheoryProblems&); //print the current 2 sets


int solve_problem(SetTheoryProblems&, size_t);



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
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cin.clear();
		//ignore incorrect input until the end of the stream or until the end of the line and clear flag of errors


		std::cout << "You are wrong! Please, repeat input from incorrect token.\n";
		std::cin >> x;

	}
	return 0;  //ok
}



int randInt(unsigned int);