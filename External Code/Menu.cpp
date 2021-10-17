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

	std::string str;
	std::getline(std::cin, str);

	if (!std::cin.good())
	{
		std::cout << "EOF" << std::endl;
		return -1;
	}

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
	};


	//Alternatives for a dialog
	//the list of alternatives
	const char* msgs[] = { "0. Quit",   "1. Generate new problems", "2. Log in to the teacher's profile" ,

										"3. Log out of teacher's profile",  "4. Show answers (only for teacher)",

										

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