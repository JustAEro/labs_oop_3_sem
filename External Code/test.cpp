#include <gtest/gtest.h>
#include "SetTheoryProblems.h"

TEST(TestCaseName, TestName) {
	auto templates = SetTheoryProblems::getProblemsTemplates();
	
	ASSERT_TRUE(templates[0] ==  "The sets A = # and B = # are given. Find the union of sets A and B (A | B)");
	ASSERT_TRUE(templates[1] == "The sets A = # and B = # are given. Find the intersection of sets A and B (A & B)");
	ASSERT_TRUE(templates[2] == "The sets A = # and B = # are given. Find the difference of A and B (A \\ B)");
	ASSERT_TRUE(templates[3] == "The sets A = # and B = # are given. Find the symmetric difference of A and B (A ^ B)");

	ASSERT_TRUE(SetTheoryProblems::getCountOfProblems() == 4);
}
