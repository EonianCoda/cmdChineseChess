#include"AI.h"
#define LAYERS 4 
namespace {
	const int Originalscores[15] = { 0,10000,20,20,200,100,101,9,10000,20,20,200,100,101,9 };
	const int Originalpriority[7] = { 4,5,6,3,2,7,1 };
	pair<int, int> Deadpos{ -1,-1 };

	//"　將士象車馬包卒帥仕相車傌炮兵";
}

AI* AI::Instance = new AI;
AI* AI::getInstance()
{
	if (AI::Instance == NULL) {
		AI::Instance = new AI;
	}
	return AI::Instance;
}

void AI::initLogic()
{
	for (int i = 0; i < 15; i++) {
		scores[i] = Originalscores[i];
	}
	for (int i = 0; i < 7; i++) {
		ChessBoard::Instance->priority[i] = Originalpriority[i];
	}
}

void AI::ChangeLogic()
{
	scores[4] = 200 + (2 - ChessBoard::Instance->chessPos[4].size()) * 50;
	scores[11] = 200 + (2 - ChessBoard::Instance->chessPos[11].size()) * 50;

	scores[6] = 101 + (2 - ChessBoard::Instance->chessPos[6].size()) * 50;
	scores[13] = 101 + (2 - ChessBoard::Instance->chessPos[13].size()) * 50;

	scores[5] = 100 + (2 - ChessBoard::Instance->chessPos[5].size()) * 50;
	scores[12] = 100 + (2 - ChessBoard::Instance->chessPos[12].size()) * 50;
}

AI::AI()
{
}


pair<int, pair<Coordinate, Coordinate>> AI::getBest()
{
	clock_t start = clock();
	auto steps = ChessBoard::Instance->AIfilter(0);
	int Min = INT_MAX, Max = INT_MIN, curScore;
	pair<int, int> ans;
	vector<Coordinate>::iterator iter;
	int i = -1, j = -1;
	int* startPos, * endPos;
	bool flag = false;
	initLogic();
	ChangeLogic();
	for (auto Chess : *steps) {
		if (flag) {
			break;
		}
		i++;
		j = -1;
		for (auto destination : Chess.second) {
			j++;
			nowScore = 0;
			if (destination.first == 8) {
				ans.first = i;
				ans.second = j;
				flag = true;
				break;
			}
			for (auto& item : ChessBoard::Instance->chessPos[Chess.first.first]) {
				if (item == Chess.first.second) {
					item = move(destination.second);
					break;
				}
			}
			startPos = &ChessBoard::Instance->board[Chess.first.second.first][Chess.first.second.second];
			endPos = &ChessBoard::Instance->board[destination.second.first][destination.second.second];
			*startPos = 0;
			*endPos = Chess.first.first;
			if (destination.first) {
				nowScore += scores[destination.first];
				for (iter = ChessBoard::Instance->chessPos[destination.first].begin();; iter++) {
					if (*iter == destination.second) {
						ChessBoard::Instance->chessPos[destination.first].erase(iter);
						break;
					}
				}
			}


			curScore = ((LAYERS - 1 == 0) ? nowScore : getMinScore(LAYERS - 1, Min, Max));
			if (curScore > Max) {
				Max = curScore;
				ans.first = i;
				ans.second = j;
			}


			*startPos = Chess.first.first;
			for (auto& item : ChessBoard::Instance->chessPos[Chess.first.first]) {
				if (item == destination.second) {
					item = move(Chess.first.second);
					break;
				}
			}
			*endPos = destination.first;
			if (destination.first) {
				nowScore -= scores[destination.first];
				ChessBoard::Instance->chessPos[destination.first].emplace_back(move(destination.second));
			}
		}
	}

	pair<int, pair<Coordinate, Coordinate>> result{ steps->at(ans.first).first.first, {steps->at(ans.first).first.second,steps->at(ans.first).second[ans.second].second} };
	delete steps;
	clock_t end = clock();
	timeSpend.push_back((double)(end - start) / CLOCKS_PER_SEC);
	return result;
}

int AI::getMinScore(int layer, int Min, int Max)
{
	auto steps = ChessBoard::Instance->AIfilter(1);
	int curScore, * startPos, * endPos;
	vector<Coordinate>::iterator iter;

	for (auto Chess : *steps) {
		for (auto destination : Chess.second) {
			if (destination.first == 1) {
				return INT_MIN + 1;
			}



			for (auto& item : ChessBoard::Instance->chessPos[Chess.first.first]) {
				if (item == Chess.first.second) {
					item = destination.second;
					break;
				}
			}
			startPos = &ChessBoard::Instance->board[Chess.first.second.first][Chess.first.second.second];
			endPos = &ChessBoard::Instance->board[destination.second.first][destination.second.second];
			*startPos = 0;
			*endPos = Chess.first.first;
			if (destination.first) {
				nowScore -= scores[destination.first];

				for (iter = ChessBoard::Instance->chessPos[destination.first].begin();; iter++) {
					if (*iter == destination.second) {
						ChessBoard::Instance->chessPos[destination.first].erase(iter);
						break;
					}
				}
			}
			curScore = ((layer == 1) ? nowScore : getMaxScore(layer - 1, Min, Max));
			if (curScore < Min) {
				Min = curScore;
				if (Max > Min) {
					*startPos = Chess.first.first;
					for (auto& item : ChessBoard::Instance->chessPos[Chess.first.first]) {
						if (item == destination.second) {
							item = move(Chess.first.second);
							break;
						}
					}
					*endPos = destination.first;
					if (destination.first) {
						nowScore += scores[destination.first];
						ChessBoard::Instance->chessPos[destination.first].emplace_back(move(destination.second));
					}
					delete steps;
					return Min;
				}
			}
			*startPos = Chess.first.first;
			for (auto& item : ChessBoard::Instance->chessPos[Chess.first.first]) {
				if (item == destination.second) {
					item = move(Chess.first.second);
					break;
				}
			}
			*endPos = destination.first;
			if (destination.first) {
				nowScore += scores[destination.first];
				ChessBoard::Instance->chessPos[destination.first].emplace_back(move(destination.second));
			}

		}
	}
	delete steps;
	return Min;
}

int AI::getMaxScore(int layer, int Min, int Max)
{
	auto steps = ChessBoard::Instance->AIfilter(0);
	int curScore, * startPos, * endPos;
	vector<Coordinate>::iterator iter;
	for (auto Chess : *steps) {
		for (auto destination : Chess.second) {
			if (destination.first == 8) {
				return INT_MAX - 1;
			}

			for (auto& item : ChessBoard::Instance->chessPos[Chess.first.first]) {
				if (item == Chess.first.second) {
					item = destination.second;
					break;
				}
			}
			startPos = &ChessBoard::Instance->board[Chess.first.second.first][Chess.first.second.second];
			endPos = &ChessBoard::Instance->board[destination.second.first][destination.second.second];
			*startPos = 0;
			*endPos = Chess.first.first;
			if (destination.first) {
				nowScore += scores[destination.first];

				for (iter = ChessBoard::Instance->chessPos[destination.first].begin();; iter++) {
					if (*iter == destination.second) {
						ChessBoard::Instance->chessPos[destination.first].erase(iter);
						break;
					}
				}
			}

			curScore = ((layer == 1) ? nowScore : getMinScore(layer - 1, Min, Max));
			if (curScore > Max) {
				Max = curScore;
				if (Max > Min) {
					*startPos = Chess.first.first;
					for (auto& item : ChessBoard::Instance->chessPos[Chess.first.first]) {
						if (item == destination.second) {
							item = move(Chess.first.second);
							break;
						}
					}
					*endPos = destination.first;
					if (destination.first) {
						nowScore -= scores[destination.first];
						ChessBoard::Instance->chessPos[destination.first].emplace_back(move(destination.second));
					}
					delete steps;
					return Max;
				}

			}

			*startPos = Chess.first.first;
			for (auto& item : ChessBoard::Instance->chessPos[Chess.first.first]) {
				if (item == destination.second) {
					item = move(Chess.first.second);
					break;
				}
			}
			*endPos = destination.first;
			if (destination.first) {
				nowScore -= scores[destination.first];
				ChessBoard::Instance->chessPos[destination.first].emplace_back(move(destination.second));
			}
		}
	}
	delete steps;
	return Max;
}
