#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <random>
#include <ctime>

class Question
{
private:
	std::string _m_question;
	std::vector<std::string> _m_possibleAnswers;
public:
	Question(std::string m_question, std::vector<std::string> m_possibleAnswers);
	Question(const Question & other);
	~Question();
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	std::string getCurrectAnswer();
	int shufleQuestion();

};