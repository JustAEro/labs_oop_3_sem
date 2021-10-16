#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DynSet.h"
#include "SetTheoryProblems.h"

int main(int argc, char* argv[])
{
	Set new_set(228);


	std::ostringstream ostring;
	ostring << new_set;
	std::cout << ostring.str() << std::endl;

	std::cout << new_set << std::endl;

	
	return 0;
}