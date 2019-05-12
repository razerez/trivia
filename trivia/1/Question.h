#pragma once

#include <iostream>
#include <vector>

class Question
{
private:
	std::string _m_question;
	std::vector<std::string> _m_possibleAnswers;
public:
	Question(std::string m_question, std::vector<std::string> m_possibleAnswers);
	~Question();
	std::string getQuestion();
	std::string getPossibleAnswers();
	std::string getCurrectAnswer();

};