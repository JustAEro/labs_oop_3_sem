#include "SetTheoryProblems.h"

const std::string SetTheoryProblems::password = "sudo";

const std::string SetTheoryProblems::problemsTemplates[SetTheoryProblems::COUNT_OF_PROBLEMS] =  
{	"The sets A = # and B = # are given. Find the union of sets A and B (A | B).",
	"The sets A = # and B = # are given. Find the intersection of sets A and B (A & B).",
	"The sets A = # and B = # are given. Find the difference of A and B (A \\ B).",
	"The sets A = # and B = # are given. Find the symmetric difference of A and B (A ^ B)."
} ;


SetTheoryProblems::SetTheoryProblems(const Set& set1, const Set& set2) : A(set1), B(set2), isTeacher(false)
{
	SetTheoryProblems::generateProblems();
	SetTheoryProblems::calculateAnswers();
}


SetTheoryProblems& SetTheoryProblems::setA(const Set& set) noexcept
{
	A = set; 
	SetTheoryProblems::generateProblems();
	SetTheoryProblems::calculateAnswers(); 
	return *this;
}

SetTheoryProblems& SetTheoryProblems::setB(const Set& set) noexcept 
{ 
	B = set; 
	SetTheoryProblems::generateProblems();
	SetTheoryProblems::calculateAnswers();
	return *this; 
}


SetTheoryProblems& SetTheoryProblems::generateProblems() noexcept
{
	std::ostringstream oss;

	for (size_t i = 0; i < COUNT_OF_PROBLEMS; ++i)
	{
		std::string str = problemsTemplates[i];

		oss << A;
		str.insert(str.find('#'), oss.str());
		str.erase(str.find('#'), 1);

		oss.str("");

		oss << B;

		str.insert(str.rfind('#'), oss.str());
		str.erase(str.rfind('#'), 1);

		problems[i] = str;
		oss.str("");
	}
	
	return *this;
}


SetTheoryProblems& SetTheoryProblems::calculateAnswers() noexcept
{
	answers[0] = A | B;
	answers[1] = A & B;
	answers[2] = A - B;
	answers[3] = (A - B) | (B - A);
	
	return *this;
}


