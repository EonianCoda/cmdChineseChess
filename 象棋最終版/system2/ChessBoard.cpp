#include"ChessBoard.h"
#include<iostream>
#define LAYER 4
namespace {
	Coordinate Illegal{ -1,-1 };
	const int priority[7] = { 5,4,6,3,2,1,7 };
	//"　將士象車馬包卒帥仕相車傌炮兵";
}

ChessBoard* ChessBoard::Instance = new ChessBoard;
ChessBoard::ChessBoard()
{
	vector<int>temp;
	board.push_back({ 4 ,5 ,3 ,2 ,1 ,2 ,3 ,5 ,4 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,6 ,0 ,0 ,0 ,0 ,0 ,6 ,0 });
	board.push_back({ 7 ,0 ,7 ,0 ,7,0 ,7 ,0 ,7 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 14,0 ,14,0 ,14,0 ,14,0 ,14 });
	board.push_back({ 0 ,13,0 ,0 ,0 ,0 ,0 ,13,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 11,12,10,9 ,8 ,9 ,10,12,11 });
	chessPos.clear();
	chessPos = { {},{},{},{},{},{},{},{},{},{},{},{},{},{},{} };
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			Coordinate temp = make_pair(i, j);
			if (check(temp)) {
				chessPos[check(temp)].push_back(temp);
			}
		}
	}
	historyBoard.first = false;
}
int ChessBoard::check(const Coordinate& co)
{
	if (co.first < 0 || co.first>9 || co.second < 0 || co.second>8) {
		return -1;
	}
	return board[co.first][co.second];
}
void ChessBoard::init()
{
	vector<int>temp;
	board.clear();
	board.push_back({ 4 ,5 ,3 ,2 ,1 ,2 ,3 ,5 ,4 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,6 ,0 ,0 ,0 ,0 ,0 ,6 ,0 });
	board.push_back({ 7 ,0 ,7 ,0 ,7 ,0 ,7 ,0 ,7 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 14,0 ,14,0 ,14,0 ,14,0 ,14 });
	board.push_back({ 0 ,13,0 ,0 ,0 ,0 ,0 ,13,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 11,12,10,9 ,8 ,9 ,10,12,11 });
	chessPos = { {},{},{},{},{},{},{},{},{},{},{},{},{},{},{} };
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			Coordinate temp = make_pair(i, j);
			if (check(temp)) {
				chessPos[check(temp)].push_back(temp);
			}
		}
	}
	historyBoard.first = false;
}
//載入圖 vector<vector<int>>
void ChessBoard::load(int player,vector<vector<int>>input)
{
	board = input;
	chessPos.clear();
	chessPos = { {},{},{},{},{},{},{},{},{},{},{},{},{},{},{}, };
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			Coordinate temp = make_pair(i, j);
			if (check(temp)) {
				chessPos[check(temp)].push_back(temp);
			}
		}
	}
	historyBoard.first = true;
	historyBoard.second.first = player;
	historyBoard.second.second = input;
}

//白棋盤
void ChessBoard::clear()
{
	board.clear();
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	board.push_back({ 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 });
	chessPos.clear();
	chessPos = { {},{},{},{},{},{},{},{},{},{},{},{},{},{},{}, };
}

//修改棋盤
void ChessBoard::modify(const int& chessNum, const Coordinate& from, const Coordinate& to)
{
	if (from != Illegal) {
		if (to == Illegal) {
			for (int i = 0; i < chessPos[chessNum].size(); i++) {
				if (chessPos[chessNum][i] == from) {
					chessPos[chessNum].erase(chessPos[chessNum].begin() + i);
					break;
				}
			}
			board[from.first][from.second] = 0;
		}
		else {
			for (int i = 0; i < chessPos[chessNum].size(); i++) {
				if (chessPos[chessNum][i] == from) {
					chessPos[chessNum][i] = to;
					break;
				}
			}
			board[from.first][from.second] = 0;
			board[to.first][to.second] = chessNum;
		}
	}
	else {
		chessPos[chessNum].push_back(to);
		board[to.first][to.second] = chessNum;
	}

}
//檢查是否將軍
bool ChessBoard::ifCheckmate(bool curPlayer)
{
	if (curPlayer) {
		for (int i : {4, 5, 6, 7}) {
			for (auto j : chessPos[i]) {
				vector<pair<int, pair<int, int>>>* temp = filter(j);
				for (auto k : *temp) {
					if (check(k.second) == 8)
						return 1;
				}
			}
		}
	}
	else {
		for (int i : {11, 12, 13, 14}) {
			for (auto j : chessPos[i]) {
				vector<pair<int, pair<int, int>>>* temp = filter(j);
				for (auto k : *temp) {
					if (check(k.second) == 1)
						return 1;
				}
			}
		}
	}
	return 0;
}

int ChessBoard::getChessNum(int chessNum)
{
	return chessPos[chessNum].size();
}

//回傳圖 vector<vector<int>>
vector<vector<int>> ChessBoard::getBoard()
{
	return board;
}
//(被吃的子,目標位置) vector<pair<int, pair<int, int>>>
vector<pair<int, Coordinate>>* ChessBoard::filter(const Coordinate & curCo)
{
	vector<pair<int, pair<int, int>>>* availableStep = new vector<pair<int, pair<int, int>>>;
	int chessNum = board[curCo.first][curCo.second];
	register int destination;
	register Coordinate nextStep, j;
	//車或炮
	if (chessNum == 4 || chessNum == 6 || chessNum == 11 || chessNum == 13) {
		for (nextStep.first = curCo.first + 1, nextStep.second = curCo.second; nextStep.first <= 9; nextStep.first++) {
			destination = board[nextStep.first][nextStep.second];
			if (destination) {
				if ((chessNum == 4 || chessNum == 11)) {
					if ((destination >= 8) ^ (chessNum >= 8))
						availableStep->emplace_back(pair<int, Coordinate>(destination, nextStep));
				}
				else {
					do {
						nextStep.first++;
					} while (nextStep.first <= 9 && !board[nextStep.first][nextStep.second]);
					if (nextStep.first != 10 && ((board[nextStep.first][nextStep.second] >= 8) ^ (chessNum >= 8)))
						availableStep->emplace_back(pair<int, Coordinate>(board[nextStep.first][nextStep.second], nextStep));
				}
				break;
			}
			else
				availableStep->emplace_back(pair<int, Coordinate>(0, nextStep));
		}
		for (nextStep.first = curCo.first - 1, nextStep.second = curCo.second; nextStep.first >= 0; nextStep.first--) {
			destination = board[nextStep.first][nextStep.second];
			if (destination) {
				if ((chessNum == 4 || chessNum == 11)) {
					if ((destination >= 8) ^ (chessNum >= 8))
						availableStep->emplace_back(pair<int, Coordinate>(destination, nextStep));
				}
				else {
					do {
						nextStep.first--;
					} while (nextStep.first >= 0 && !board[nextStep.first][nextStep.second]);
					if (nextStep.first != -1 && ((board[nextStep.first][nextStep.second] >= 8) ^ (chessNum >= 8)))
						availableStep->emplace_back(pair<int, Coordinate>(board[nextStep.first][nextStep.second], nextStep));
				}
				break;
			}
			else
				availableStep->emplace_back(pair<int, Coordinate>(0, nextStep));
		}
		for (nextStep.first = curCo.first, nextStep.second = curCo.second + 1; nextStep.second <= 8; nextStep.second++) {
			destination = board[nextStep.first][nextStep.second];
			if (destination) {
				if ((chessNum == 4 || chessNum == 11)) {
					if ((destination >= 8) ^ (chessNum >= 8))
						availableStep->emplace_back(pair<int, Coordinate>(destination, nextStep));
				}
				else {
					do {
						nextStep.second++;
					} while (nextStep.second <= 8 && !board[nextStep.first][nextStep.second]);
					if (nextStep.second != 9 && ((board[nextStep.first][nextStep.second] >= 8) ^ (chessNum >= 8)))
						availableStep->emplace_back(pair<int, Coordinate>(board[nextStep.first][nextStep.second], nextStep));
				}
				break;
			}
			else
				availableStep->emplace_back(pair<int, Coordinate>(0, nextStep));
		}
		for (nextStep.first = curCo.first, nextStep.second = curCo.second - 1; nextStep.second >= 0; nextStep.second--) {
			destination = board[nextStep.first][nextStep.second];
			if (destination) {
				if ((chessNum == 4 || chessNum == 11)) {
					if ((destination >= 8) ^ (chessNum >= 8))
						availableStep->emplace_back(pair<int, Coordinate>(destination, nextStep));
				}
				else {
					do {
						nextStep.second--;
					} while (nextStep.second >= 0 && !board[nextStep.first][nextStep.second]);
					if (nextStep.second != -1 && ((board[nextStep.first][nextStep.second] >= 8) ^ (chessNum >= 8)))
						availableStep->emplace_back(pair<int, Coordinate>(board[nextStep.first][nextStep.second], nextStep));
				}
				break;
			}
			else
				availableStep->emplace_back(pair<int, Coordinate>(0, nextStep));
		}
		return availableStep;
	}
	//非車非炮
	for (auto i : MOVE_LIST[chessNum]) {
		nextStep.first = curCo.first + i.first;
		nextStep.second = curCo.second + i.second;
		bool ifpb = 0;
		if (nextStep.first >= 0 && nextStep.first <= 9 && nextStep.second >= 0 && nextStep.second <= 8) {
			if (chessNum == 1 && nextStep.second >= 3 && nextStep.second <= 5 && nextStep.first <= 2) {
				if (i.first != 0 || i.second != 0)
					ifpb = 1;
				else {
					j.first = nextStep.first + 1;
					j.second = nextStep.second;
					for (; j.first <= 9; j.first++) {
						destination = board[j.first][j.second];
						if (destination == 8) {
							nextStep = j;
							ifpb = 1;
						}
						else if (destination != 0)
							break;
					}
				}
			}
			else if (chessNum == 8 && nextStep.second >= 3 && nextStep.second <= 5 && nextStep.first >= 7) {
				if (i.first != 0 || i.second != 0)
					ifpb = 1;
				else {
					j.first = nextStep.first - 1;
					j.second = nextStep.second;
					for (; j.first >= 0; j.first--) {
						destination = board[j.first][j.second];
						if (destination == 1) {
							nextStep = j;
							ifpb = 1;
						}
						else if (destination != 0)
							break;
					}
				}
			}
			else if (chessNum == 2 && nextStep.second >= 3 && nextStep.second <= 5 && nextStep.first <= 2) {
				ifpb = 1;
			}
			else if (chessNum == 9 && nextStep.second >= 3 && nextStep.second <= 5 && nextStep.first >= 7) {
				ifpb = 1;
			}
			else if ((chessNum == 3 || chessNum == 10) && !board[curCo.first + (i.first / 2)][curCo.second + (i.second / 2)]) {
				if (chessNum < 7 && nextStep.first <= 4 ||
					chessNum >= 7 && nextStep.first >= 5)
					ifpb = 1;
			}
			else if (chessNum == 5 || chessNum == 12) {
				if (abs(i.first) == 2 && !board[curCo.first + (int)(i.first / (int)abs(i.first))][curCo.second] ||
					abs(i.second) == 2 && !board[curCo.first][curCo.second + (i.second / (int)abs(i.second))])
					ifpb = 1;
			}
			else if (chessNum == 7) {
				if (curCo.first > 4)
					ifpb = 1;
				else if (i.first)
					ifpb = 1;
			}
			else if (chessNum == 14) {
				if (curCo.first < 5)
					ifpb = 1;
				else if (i.first)
					ifpb = 1;
			}
			//判斷結束
			if (ifpb) {
				destination = board[nextStep.first][nextStep.second];
				if (!destination) {
					availableStep->emplace_back(pair<int, Coordinate>(0, nextStep));
				}
				else if ((destination >= 8) ^ (chessNum >= 8)) {
					availableStep->emplace_back(pair<int, Coordinate>(destination, nextStep));
				}
			}
		}
	}
	return availableStep;
}

//(被吃的子,目標位置) vector<pair<int, pair<int, int>>>
vector< pair< pair<int, Coordinate>, vector<pair<int, Coordinate>>> >* ChessBoard::AIfilter(bool player)
{
	vector< pair< pair<int, Coordinate>, vector<pair<int, Coordinate>>> >* Steps = new vector< pair< pair<int, Coordinate>, vector<pair<int, Coordinate>>>  >;
	Steps->reserve(16);
	vector<pair<int, Coordinate>>* availableStep;
	int chessNum;
	register int destination;
	register Coordinate nextStep, j;

	for (auto nowChess : priority) {
		if (player) nowChess += 7;
		for (auto curCo : chessPos[nowChess]) {
			Steps->emplace_back(pair< pair<int, Coordinate>, vector<pair<int, Coordinate>>>{ {nowChess, curCo}, {}});
			availableStep = &Steps->back().second;
			chessNum = nowChess;
			//車或炮
			if (chessNum == 4 || chessNum == 6 || chessNum == 11 || chessNum == 13) {
				availableStep->reserve(17);
				for (nextStep.first = curCo.first + 1, nextStep.second = curCo.second; nextStep.first <= 9; nextStep.first++) {
					destination = board[nextStep.first][nextStep.second];
					if (destination) {
						if ((chessNum == 4 || chessNum == 11)) {
							if ((destination >= 8) ^ (chessNum >= 8))
								availableStep->emplace_back(pair<int, Coordinate>(destination, nextStep));
						}
						else {
							do {
								nextStep.first++;
							} while (nextStep.first <= 9 && !board[nextStep.first][nextStep.second]);
							if (nextStep.first != 10 && ((board[nextStep.first][nextStep.second] >= 8) ^ (chessNum >= 8)))
								availableStep->emplace_back(pair<int, Coordinate>(board[nextStep.first][nextStep.second], nextStep));
						}
						break;
					}
					else
						availableStep->emplace_back(pair<int, Coordinate>(0, nextStep));
				}
				for (nextStep.first = curCo.first - 1, nextStep.second = curCo.second; nextStep.first >= 0; nextStep.first--) {
					destination = board[nextStep.first][nextStep.second];
					if (destination) {
						if ((chessNum == 4 || chessNum == 11)) {
							if ((destination >= 8) ^ (chessNum >= 8))
								availableStep->emplace_back(pair<int, Coordinate>(destination, nextStep));
						}
						else {
							do {
								nextStep.first--;
							} while (nextStep.first >= 0 && !board[nextStep.first][nextStep.second]);
							if (nextStep.first != -1 && ((board[nextStep.first][nextStep.second] >= 8) ^ (chessNum >= 8)))
								availableStep->emplace_back(pair<int, Coordinate>(board[nextStep.first][nextStep.second], nextStep));
						}
						break;
					}
					else
						availableStep->emplace_back(pair<int, Coordinate>(0, nextStep));
				}
				for (nextStep.first = curCo.first, nextStep.second = curCo.second + 1; nextStep.second <= 8; nextStep.second++) {
					destination = board[nextStep.first][nextStep.second];
					if (destination) {
						if ((chessNum == 4 || chessNum == 11)) {
							if ((destination >= 8) ^ (chessNum >= 8))
								availableStep->emplace_back(pair<int, Coordinate>(destination, nextStep));
						}
						else {
							do {
								nextStep.second++;
							} while (nextStep.second <= 8 && !board[nextStep.first][nextStep.second]);
							if (nextStep.second != 9 && ((board[nextStep.first][nextStep.second] >= 8) ^ (chessNum >= 8)))
								availableStep->emplace_back(pair<int, Coordinate>(board[nextStep.first][nextStep.second], nextStep));
						}
						break;
					}
					else
						availableStep->emplace_back(pair<int, Coordinate>(0, nextStep));
				}
				for (nextStep.first = curCo.first, nextStep.second = curCo.second - 1; nextStep.second >= 0; nextStep.second--) {
					destination = board[nextStep.first][nextStep.second];
					if (destination) {
						if ((chessNum == 4 || chessNum == 11)) {
							if ((destination >= 8) ^ (chessNum >= 8))
								availableStep->emplace_back(pair<int, Coordinate>(destination, nextStep));
						}
						else {
							do {
								nextStep.second--;
							} while (nextStep.second >= 0 && !board[nextStep.first][nextStep.second]);
							if (nextStep.second != -1 && ((board[nextStep.first][nextStep.second] >= 8) ^ (chessNum >= 8)))
								availableStep->emplace_back(pair<int, Coordinate>(board[nextStep.first][nextStep.second], nextStep));
						}
						break;
					}
					else
						availableStep->emplace_back(pair<int, Coordinate>(0, nextStep));
				}
			}
			//非車非炮
			else {
				availableStep->reserve(8);
				for (auto i : MOVE_LIST[chessNum]) {
					nextStep.first = curCo.first + i.first;
					nextStep.second = curCo.second + i.second;
					bool ifpb = 0;
					if (nextStep.first >= 0 && nextStep.first <= 9 && nextStep.second >= 0 && nextStep.second <= 8) {
						if (chessNum == 1 && nextStep.second >= 3 && nextStep.second <= 5 && nextStep.first <= 2) {
							if (i.first != 0 || i.second != 0)
								ifpb = 1;
							else {
								j.first = nextStep.first + 1;
								j.second = nextStep.second;
								for (; j.first <= 9; j.first++) {
									destination = board[j.first][j.second];
									if (destination == 8) {
										nextStep = j;
										ifpb = 1;
									}
									else if (destination != 0)
										break;
								}
							}
						}
						else if (chessNum == 8 && nextStep.second >= 3 && nextStep.second <= 5 && nextStep.first >= 7) {
							if (i.first != 0 || i.second != 0)
								ifpb = 1;
							else {
								j.first = nextStep.first - 1;
								j.second = nextStep.second;
								for (; j.first >= 0; j.first--) {
									destination = board[j.first][j.second];
									if (destination == 1) {
										nextStep = j;
										ifpb = 1;
									}
									else if (destination != 0)
										break;
								}
							}
						}
						else if (chessNum == 2 && nextStep.second >= 3 && nextStep.second <= 5 && nextStep.first <= 2) {
							ifpb = 1;
						}
						else if (chessNum == 9 && nextStep.second >= 3 && nextStep.second <= 5 && nextStep.first >= 7) {
							ifpb = 1;
						}
						else if ((chessNum == 3 || chessNum == 10) && !board[curCo.first + (i.first / 2)][curCo.second + (i.second / 2)]) {
							if (chessNum < 7 && nextStep.first <= 4 ||
								chessNum >= 7 && nextStep.first >= 5)
								ifpb = 1;
						}
						else if (chessNum == 5 || chessNum == 12) {
							if (abs(i.first) == 2 && !board[curCo.first + (int)(i.first / (int)abs(i.first))][curCo.second] ||
								abs(i.second) == 2 && !board[curCo.first][curCo.second + (i.second / (int)abs(i.second))])
								ifpb = 1;
						}
						else if (chessNum == 7) {
							if (curCo.first > 4)
								ifpb = 1;
							else if (i.first)
								ifpb = 1;
						}
						else if (chessNum == 14) {
							if (curCo.first < 5)
								ifpb = 1;
							else if (i.first)
								ifpb = 1;
						}
						//判斷結束
						if (ifpb) {
							destination = board[nextStep.first][nextStep.second];
							if (!destination) {
								availableStep->emplace_back(pair<int, Coordinate>(0, nextStep));
							}
							else if ((destination >= 8) ^ (chessNum >= 8)) {
								availableStep->emplace_back(pair<int, Coordinate>(destination, nextStep));
							}
						}
					}
				}
			}
		}
	}
	return Steps;
}


// 檢查是否有歷史棋盤
pair<bool, pair<int, vector<vector<int>>  > >ChessBoard::CheckHistory()
{
	return historyBoard;
}
