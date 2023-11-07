#pragma once
#include"ChessBoard.h"
#include<ctime>
using namespace std;
class AI {
public:
	static AI* getInstance();
	AI();
	pair<int, pair<Coordinate, Coordinate>> getBest();

private:
	static AI* Instance;

	int getMinScore(int layer, int Min, int Max);
	int getMaxScore(int layer, int Min, int Max);

	void initLogic();
	void ChangeLogic();
	
	vector<double> timeSpend;
	int scores[15];
	int nowScore;
};


