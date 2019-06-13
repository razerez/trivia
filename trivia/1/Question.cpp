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

std::string Question::getPossibleAnswers()
{
	std::string possibleAnswer =  this->_m_possibleAnswers.back();
	this->_m_possibleAnswers.pop_back();
	return possibleAnswer;
}

std::string Question::getCurrectAnswer()
{
	return this->_m_possibleAnswers[0];
}

