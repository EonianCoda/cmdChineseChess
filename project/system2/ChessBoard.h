#pragma once
#ifndef H_CHESS_BOARD
#define H_CHESS_BOARD
#include"Rule.h"
#include<vector>
#include<utility>
#include<cmath>
using namespace std;

//extern vector< vector< pair< pair<int, Coordinate>, vector<pair<int, Coordinate>>> > > AllLayer;

class ChessBoard {
public:
	static ChessBoard* Instance;
	ChessBoard();
	int check(const Coordinate&);
	void init();
	void load(int player,vector<vector<int>>);
	void clear();
	void modify(const int& chessNum, const Coordinate& from, const Coordinate& to);
	bool ifCheckmate(bool curplayer);
	int getChessNum(int chessNum);
	vector<vector<int>> getBoard();
	vector<pair<int, pair<int, int>>>* filter(const Coordinate& curCo);
	vector< pair< pair<int, Coordinate>, vector<pair<int, Coordinate>>> >* AIfilter(bool player);
	// ÀË¬d¬O§_¦³¾ú¥v´Ñ½L
	pair<bool, pair<int, vector<vector<int>>  > >CheckHistory();

	friend class Log;
	friend class AI;
private:
	vector<vector<int>> board;
	vector<vector<Coordinate>> chessPos;
	int priority[7] = { 5,4,6,3,2,1,7 };
	pair<bool,  pair<int, vector<vector<int>>  > > historyBoard;

};

#endif // !H_CHESS_BOARD