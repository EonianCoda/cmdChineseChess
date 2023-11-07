#pragma once
#include"ChessBoard.h"
#include <iostream>
#include <string>

using namespace std;
class Log {
public:
	Log();
	void push(int, Coordinate, Coordinate);
	vector<pair<int, pair<Coordinate, Coordinate> >> pop();
	pair<int, pair<Coordinate, Coordinate> >  search(int);
	void step(int, Coordinate, Coordinate);
	void clear();
	wstring& getchingChongLog(int);
	int getLength() const;
private:
	vector<pair<int, pair<Coordinate, Coordinate> > >log;
	vector<wstring> chingChongLog;
};