#include "MyStatusResponse.h"

MyStatusResponse::MyStatusResponse(int numGames, int numRight, int numWrong, float avgTimePerQuestion)
{
	_m_avgTimePerQuestion = avgTimePerQuestion;
	_m_numGames = numGames;
	_m_numRight = numRight;
	_m_numWrong = numWrong;
}
