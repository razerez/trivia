#pragma once

#include <iostream>

using namespace std;

class Question
{
private:
	string _question;
	string _rightAnswer;
	string _wrongAnswer1;
	string _wrongAnswer2;
	string _wrongAnswer3;
public:
	Question(string question, string rightAns, string wrongAns1,
		string wrongAns2, string wrongAns3);
	~Question();




};
