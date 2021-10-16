#pragma once

#include <vector>
#include <string>

class SetTheoryProblems
{
private:
	static const size_t COUNT_OF_PROBLEMS = 4;
	static const std::string problemsTemplates[COUNT_OF_PROBLEMS];
	static const std::string password;


public:

	static const std::string (&getProblemsTemplates() noexcept) [COUNT_OF_PROBLEMS]  { return problemsTemplates; }
	static const size_t getCountOfProblems() noexcept { return COUNT_OF_PROBLEMS; }
	static const std::string& getPassword() { return password; }



};


