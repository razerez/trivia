#pragma once

struct MyStatusResponse
{
	int _m_numRight;
	int _m_numWrong;
	float _m_avgTimePerQuestion;
	int _m_numGames;
	MyStatusResponse(int numGames, int numRight, int numWrong, float avgTimePerQuestion);
};