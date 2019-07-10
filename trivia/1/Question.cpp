#include "Question.h"

Question::Question(std::string m_question, std::vector<std::string> m_possibleAnswers)
{
	this->_m_possibleAnswers = m_possibleAnswers;
	this->_m_question = m_question;
}

Question::Question(const Question & other)
{
	this->_m_question = other._m_question;
	this->_m_possibleAnswers = other._m_possibleAnswers;
}


Question::~Question()
{
}

std::string Question::getQuestion()
{
	return this->_m_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
	return this->_m_possibleAnswers;
}

std::string Question::getCurrectAnswer()
{
	return this->_m_possibleAnswers[0];
}

int Question::shufleQuestion()
{
	std::string right = this->_m_possibleAnswers[0];

	srand(time(NULL));
	int random_number;


	std::vector<std::string> vec = this->_m_possibleAnswers;

	this->_m_possibleAnswers.clear();

	int arr[4] = { -1,-1,-1,-1 };


	for (int i = 0; i < 4; i++)
	{
		random_number = std::rand() % 4;
		
		while (arr[0] == random_number || arr[1] == random_number || arr[2] == random_number || arr[3] == random_number)
		{
			random_number = std::rand() % 3;
		}
		
		arr[i] = random_number;
		this->_m_possibleAnswers.push_back(vec[random_number]);
		
	}


	int count = 0;
	bool flag = true;
	for (std::vector<std::string>::iterator it = this->_m_possibleAnswers.begin(); it != this->_m_possibleAnswers.end() && flag; ++it)
	{
		if (right == (*it))
		{
			flag = false;
		}
		count++;
	}

	return count--;
}

