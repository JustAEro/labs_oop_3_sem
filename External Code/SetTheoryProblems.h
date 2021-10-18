#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DynSet.h"

class SetTheoryProblems
{
private:
	static const size_t COUNT_OF_PROBLEMS = 4;
	static const std::string problemsTemplates[COUNT_OF_PROBLEMS];
	static const std::string password;

	Set A;
	Set B;
	std::string problems[COUNT_OF_PROBLEMS];
	bool isTeacher;
	Set answers[COUNT_OF_PROBLEMS];

	SetTheoryProblems& generateProblems() noexcept;
	SetTheoryProblems& calculateAnswers() noexcept;


public:

	SetTheoryProblems() : A(), B(), problems{}, isTeacher(false), answers{} {};
	SetTheoryProblems(const Set&, const Set&);

	static const std::string (&getProblemsTemplates() noexcept) [COUNT_OF_PROBLEMS]  { return problemsTemplates; }
	static const size_t getCountOfProblems() noexcept { return COUNT_OF_PROBLEMS; }
	static const std::string& getPassword() noexcept { return password; }

	Set const& getA() const noexcept { return A; } 
	Set const& getB() const noexcept { return B; }
	const std::string(&getProblems() const noexcept) [COUNT_OF_PROBLEMS] { return problems; }
	bool getIsTeacher() const noexcept { return isTeacher; }
	const Set(&getAnswers() const noexcept) [COUNT_OF_PROBLEMS] { return answers; }

	SetTheoryProblems& setIsTeacher(bool status) noexcept { isTeacher = status; return *this; }
	SetTheoryProblems& setA(const Set& set) noexcept;
	SetTheoryProblems& setB(const Set& set) noexcept;

};


