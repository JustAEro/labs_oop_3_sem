#include "Menu.h"


int	D_Problems_New(SetTheoryProblems& setTheoryProblems)
{
	if (setTheoryProblems.getCountOfProblems() != 0)
	{
		std::cout << "The new problems will be generated and the old ones will be deleted" << std::endl;
	}

	const size_t MAX_SIZE_OF_SET = 10;
	const unsigned int MAX_RANDOM = 50;

	Set a;
	size_t n = randInt(MAX_SIZE_OF_SET);

	for (unsigned int j = 0; j < n; ++j) 
	{
		a.insert(randInt(MAX_RANDOM));
	}

	Set b;
	n = randInt(MAX_SIZE_OF_SET);
	for (unsigned int j = 0; j < n; ++j)
	{
		b.insert(randInt(MAX_RANDOM));
	}

	setTheoryProblems.setA(a).setB(b);

	return 0;
}


int D_Log_In_Teacher(SetTheoryProblems& setTheoryProblems)
{
	if (setTheoryProblems.getIsTeacher() == true)
	{
		std::cout << "You are already in teacher's mode" << std::endl;
		return 0;
	}
	//
	std::cout << "Enter password" << std::endl;
	std::cin.ignore();

	#if defined(_WIN32)
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	#endif


	std::string str;
	std::getline(std::cin, str);

	if (!std::cin.good())
	{
		std::cout << "EOF" << std::endl;
		return -1;
	}

	#if defined(_WIN32)
	SetConsoleMode(hStdin, mode); 
    #endif

	if (setTheoryProblems.getPassword() == str)
	{
		setTheoryProblems.setIsTeacher(true);
		std::cout << "Now you are in teacher's mode. You can see the answers." << std::endl;
	}
	else
	{
		std::cout << "Wrong password! Try again!" << std::endl;
	}

	return 0;
}


int D_Log_Out_Teacher(SetTheoryProblems& setTheoryProblems)
{
	if (setTheoryProblems.getIsTeacher() == false)
	{
		std::cout << "You are not in teacher's profile now" << std::endl;
		return 0;
	}

	std::cout << "Logging out of teacher's profile" << std::endl;
	setTheoryProblems.setIsTeacher(false);
	return 0;
}


int D_Solve_Problem_Union(SetTheoryProblems& setTheoryProblems)
{
	std::cout << setTheoryProblems.getProblems()[0] << std::endl;

	size_t n = setTheoryProblems.getA().getCapacity() + setTheoryProblems.getB().getCapacity();


	std::cout << "Enter your answer (press Enter, then Ctrl+Z when you finish) --> " << std::endl;


	int* vec = new int[n];

	for (size_t i = 0; i < n; ++i)
	{
		int x;
		int status = get_T(x);

		if (status == -1)
		{
			Set answer(i, vec);

			if (answer == setTheoryProblems.getAnswers()[0])
			{
				std::cout << "Congratulations! The answer is correct." << std::endl;
			}
			else
			{
				std::cout << "Wrong answer! Try again!" << std::endl;
			}
			
			delete[] vec;
			std::cin.clear();

			return 0;
		}

		vec[i] = x;
	}

	Set answer(n, vec);

	if (answer == setTheoryProblems.getAnswers()[0])
	{
		std::cout << "Congratulations! The answer is correct." << std::endl;
	}
	else
	{
		std::cout << "Wrong answer! Try again!" << std::endl;
	}

	delete[] vec;
	return 0;
}


int D_Solve_Problem_Intersection(SetTheoryProblems& setTheoryProblems)
{
	std::cout << setTheoryProblems.getProblems()[1] << std::endl;

	size_t n = setTheoryProblems.getA().getCapacity() + setTheoryProblems.getB().getCapacity();


	std::cout << "Enter your answer (press Enter, then Ctrl+Z when you finish) --> " << std::endl;

	
	int* vec = new int[n];

	for (size_t i = 0; i < n; ++i)
	{
		int x;
		int status = get_T(x);

		if (status == -1)
		{
			Set answer(i, vec);

			if (answer == setTheoryProblems.getAnswers()[1])
			{
				std::cout << "Congratulations! The answer is correct." << std::endl;
			}
			else
			{
				std::cout << "Wrong answer! Try again!" << std::endl;
			}

			delete[] vec;
			std::cin.clear();

			return 0;
		}
		
		vec[i] = x;
	}

	Set answer(n, vec);

	if (answer == setTheoryProblems.getAnswers()[1])
	{
		std::cout << "Congratulations! The answer is correct." << std::endl;
	}
	else
	{
		std::cout << "Wrong answer! Try again!" << std::endl;
	}

	delete[] vec;
	return 0;
}


int D_Solve_Problem_Difference(SetTheoryProblems& setTheoryProblems)
{
	std::cout << setTheoryProblems.getProblems()[2] << std::endl;

	size_t n = setTheoryProblems.getA().getCapacity() + setTheoryProblems.getB().getCapacity();


	std::cout << "Enter your answer (press Enter, then Ctrl+Z when you finish) --> " << std::endl;


	int* vec = new int[n];

	for (size_t i = 0; i < n; ++i)
	{
		int x;
		int status = get_T(x);

		if (status == -1)
		{
			Set answer(i, vec);

			if (answer == setTheoryProblems.getAnswers()[2])
			{
				std::cout << "Congratulations! The answer is correct." << std::endl;
			}
			else
			{
				std::cout << "Wrong answer! Try again!" << std::endl;
			}

			delete[] vec;
			std::cin.clear();

			return 0;
		}

		vec[i] = x;
	}

	Set answer(n, vec);

	if (answer == setTheoryProblems.getAnswers()[2])
	{
		std::cout << "Congratulations! The answer is correct." << std::endl;
	}
	else
	{
		std::cout << "Wrong answer! Try again!" << std::endl;
	}

	delete[] vec;
	return 0;
}


int D_Solve_Problem_Symmetric_Difference(SetTheoryProblems& setTheoryProblems)
{
	std::cout << setTheoryProblems.getProblems()[3] << std::endl;

	size_t n = setTheoryProblems.getA().getCapacity() + setTheoryProblems.getB().getCapacity();


	std::cout << "Enter your answer (press Enter, then Ctrl+Z when you finish) --> " << std::endl;


	int* vec = new int[n];

	for (size_t i = 0; i < n; ++i)
	{
		int x;
		int status = get_T(x);

		if (status == -1)
		{
			Set answer(i, vec);

			if (answer == setTheoryProblems.getAnswers()[3])
			{
				std::cout << "Congratulations! The answer is correct." << std::endl;
			}
			else
			{
				std::cout << "Wrong answer! Try again!" << std::endl;
			}

			delete[] vec;
			std::cin.clear();

			return 0;
		}

		vec[i] = x;
	}

	Set answer(n, vec);

	if (answer == setTheoryProblems.getAnswers()[3])
	{
		std::cout << "Congratulations! The answer is correct." << std::endl;
	}
	else
	{
		std::cout << "Wrong answer! Try again!" << std::endl;
	}

	delete[] vec;
	return 0;
}


int D_Set_A(SetTheoryProblems& setTheoryProblems)
{
	if (setTheoryProblems.getIsTeacher() == false)
	{
		std::cout << "Error! You can't edit the sets if you're not a teacher!" << std::endl;
		return 0;
	}

	std::cout << "Enter the size of A: " << std::endl;

	int size_A;
	int status = get_T(size_A);

	if (status == -1) 
	{
		std::cout << "EOF" << std::endl;
		return -1;
	}

	if (size_A < 0)
	{
		std::cout << "Error! The size of set can't be < 0. Try again!" << std::endl;
		return 0;
	}

	int* vec = new int[size_A];

	if (size_A != 0)
	{
		std::cout << "Enter the elements of A: " << std::endl;
		std::cout << "Hint: If you entered larger size than needed, keep in mind:" << std::endl;
		std::cout << "Elements that are already in the set will not be added to it." << std::endl;

		std::cout << "And if you entered smaller size, you can try again by pressing Ctrl+Z." << std::endl;
	}
	
	for (int i = 0; i < size_A; ++i)
	{
		int x;
		status = get_T(x);

		if (status == -1)
		{
			std::cout << "Exiting from the function" << std::endl;
			delete[] vec;
			std::cin.clear();
			return 0;
		}

		vec[i] = x;
	}

	setTheoryProblems.setA(Set(size_A, vec));

	delete[] vec;

	return 0;
}


int D_Set_B(SetTheoryProblems& setTheoryProblems)
{
	if (setTheoryProblems.getIsTeacher() == false)
	{
		std::cout << "Error! You can't edit the sets if you're not a teacher!" << std::endl;
		return 0;
	}

	std::cout << "Enter the size of B: " << std::endl;

	int size_B;
	int status = get_T(size_B);

	if (status == -1)
	{
		std::cout << "EOF" << std::endl;
		return -1;
	}

	if (size_B < 0)
	{
		std::cout << "Error! The size of set can't be < 0. Try again!" << std::endl;
		return 0;
	}

	if (size_B != 0)
	{
		std::cout << "Enter the elements of B: " << std::endl;
		std::cout << "Hint: If you entered larger size than needed, keep in mind:" << std::endl;
		std::cout << "Elements that are already in the set will not be added to it." << std::endl;

		std::cout << "And if you entered smaller size, you can try again by pressing Ctrl+Z." << std::endl;
	}
	
	int* vec = new int[size_B];

	for (int i = 0; i < size_B; ++i)
	{
		int x;
		status = get_T(x);

		if (status == -1)
		{
			std::cout << "Exiting from the function" << std::endl;
			delete[] vec;
			std::cin.clear();
			return 0;
		}

		vec[i] = x;
	}

	setTheoryProblems.setB(Set(size_B, vec));

	delete[] vec;

	return 0;
}



int D_Show_Answers(SetTheoryProblems& setTheoryProblems)
{
	if (setTheoryProblems.getIsTeacher() == false)
	{
		std::cout << "Error! This function can only be run in the teacher's account" << std::endl;
		return 0;
	}

	Set a = setTheoryProblems.getA();
	Set b = setTheoryProblems.getB();
	std::cout << "A = " << a << std::endl;
	std::cout << "B = " << b << std::endl;


	auto problems = setTheoryProblems.getProblems();

	std::cout << std::endl;

	for (size_t i = 0; i < setTheoryProblems.getCountOfProblems(); ++i)
	{
		std::cout << (i + 1) << ") " << problems[i] << std::endl;
		std::cout << "Answer: ";

		auto answers = setTheoryProblems.getAnswers();
		std::cout << answers[i] << std::endl;
	}

	return 0;
}


int D_Print_Sets(SetTheoryProblems& setTheoryProblems)
{
	std::cout << "The current A and B are:" << std::endl;
	std::cout << "A = " << setTheoryProblems.getA() << std::endl << "B = " << setTheoryProblems.getB() << std::endl;
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


void start_menu(SetTheoryProblems& setTheoryProblems)
{
	int (*dialog_functions[])(SetTheoryProblems& setTheoryProblems) = { nullptr,	
														
														D_Problems_New,
														D_Log_In_Teacher,
														D_Log_Out_Teacher, 
														D_Show_Answers,
														D_Solve_Problem_Union,
														D_Solve_Problem_Intersection, 
														D_Solve_Problem_Difference,
													    D_Solve_Problem_Symmetric_Difference,
														D_Set_A,
														D_Set_B,
														D_Print_Sets
	};


	//Alternatives for a dialog
	//the list of alternatives
	const char* msgs[] = { "0. Quit",   "1. Generate new problems", "2. Log in to the teacher's profile" ,

										"3. Log out of teacher's profile",  "4. Show answers (only for teacher)",

										"5. Solve problem with union of two sets", "6. Solve problem with intersection of two sets",
										
										"7. Solve problem with difference of two sets", "8. Solve problem with symmetric difference of two sets",
										
										"9. Init new set A (only for teacher)", "10. Init new set B (only for teacher)",
						
										"11. Print current sets"

	};

	//the number of alternatives
	const int menu_size = sizeof(msgs) / sizeof(msgs[0]);

	int number_of_alternative;
	while ((number_of_alternative = dialog(msgs, menu_size)))
	{
		if (dialog_functions[number_of_alternative](setTheoryProblems) == -1)
		{
			break;
		}
	}

	std::cout << "That's all. Bye!" << std::endl;
}


int randInt(unsigned int maximum)
{
	std::random_device rd;
	std::mt19937 mersenne(rd());
	
	return 1 + mersenne() % maximum;
}