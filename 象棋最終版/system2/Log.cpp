#include "Log.h"

namespace {
	wchar_t list[] = L"　將士象車馬包卒帥仕相車傌炮兵";
	vector<wstring> order = { L"後前",L"後中前",L"後三二前",L"後四三二前" };
	wstring ChineseNumber = L"　一二三四五六七八九";
	wstring Number = L"　１２３４５６７８９";
}

Log::Log()
{
	log.clear();
	chingChongLog.clear();
}

void Log::clear()
{
	log.clear();
	chingChongLog.clear();
}
vector<pair<int, pair<Coordinate, Coordinate> >> Log::pop()
{
	vector<pair<int, pair<Coordinate, Coordinate> > > tmp;
	for (int i = 0; i < 4; i++)
	{
		tmp.push_back(log.back());
		log.pop_back();
	}

	chingChongLog.pop_back();
	chingChongLog.pop_back();
	return tmp;
}
void Log::push(int chessNum, Coordinate from, Coordinate to)
{
	log.push_back(make_pair(ChessBoard::Instance->check(to), make_pair(to, make_pair(-1, -1))));
	log.push_back(make_pair(chessNum, make_pair(from, to)));

	step(chessNum, from, to);
}

wstring& Log::getchingChongLog(int index)
{
	if (index < chingChongLog.size())
	{
		return chingChongLog[index];
	}
	else
	{
		cout << "Log::getchingChongLog錯誤：" << index << endl;
		return chingChongLog[0];
	}
}

//獲取chingChongLog長度
int Log::getLength() const
{
	return (int)(chingChongLog.size());
}
pair<int, pair<Coordinate, Coordinate>>  Log::search(int n)
{
	return log[(n * 2) - 1];
}

//加入中文Log
void Log::step(int chessNum, Coordinate from, Coordinate to)
{
	wstring output = L"";
	int count = 0, pos;

	//若chessNum不合法
	if (chessNum > 14 || chessNum < 0)
	{
		cout << "Log::step錯誤：" << chessNum << endl;
		return;
	}

	//尋找直行上有幾顆相同的棋子
	for (int i = 0; i < 10; i++)
	{
		if (chessNum == ChessBoard::Instance->board[i][from.second])
		{
			//為要移動的那顆棋子
			if (from.first == i)
			{
				pos = count;
			}
			count++;

		}
	}

	output += to_wstring(chingChongLog.size() + 1);

	//黑方
	if (chessNum < 8)
	{
		output += L" 黑：";
		//第一字
		if (count == 1) //代表該路上這類型的棋子僅有一顆
		{
			output += list[chessNum]; //棋子
		}
		else
		{
			output += order[count - 2][pos];
		}

		output += L" "; //空格
		//第二字
		if (count == 1)
		{
			output += Number[from.second + 1];//加入阿拉伯數字
		}
		else
		{
			output += list[chessNum]; //棋子
		}


		output += L" "; //空格
		//第三字
		if (from.first == to.first)
		{
			output += L"平";
		}
		else if (to.first > from.first)
		{
			output += L"進";
		}
		else if (to.first < from.first)
		{
			output += L"退";
		}

		output += L" "; //空格
		//第四字
		if (from.second == to.second) //直行
		{
			output += Number[abs(from.first - to.first)];
		}

		else //斜行或橫行
		{
			output += Number[to.second + 1];
		}

	}
	//紅方
	else if (chessNum >= 8)
	{
		output += L" 紅：";
		//第一字
		if (count == 1) //代表該路上這類型的棋子僅有一顆
		{
			output += list[chessNum];//棋子
		}
		else
		{
			//若為紅方，方向要倒過來
			pos = count - 1 - pos;
			output += order[count - 2][pos];
		}


		output += L" "; //空格
		//第二字
		if (count == 1) //代表該路上這類型的棋子僅有一顆
		{
			output += ChineseNumber[10 - (from.second + 1)];//紅方漢字
		}
		else
		{
			output += list[chessNum];//棋子
		}

		output += L" "; //空格
		//第三字
		if (from.first == to.first)
		{
			output += L"平";
		}
		else if (to.first < from.first)
		{
			output += L"進";
		}
		else if (to.first > from.first)
		{
			output += L"退";
		}

		output += L" "; //空格
		//第四字
		if (from.second == to.second)//直行
		{
			output += ChineseNumber[abs(from.first - to.first)];
			//chingChongLog.push_back(abs(from.first - to.first));//前進步數  (漢)
		}
		//斜行或橫行
		else
		{
			output += ChineseNumber[10 - (to.second + 1)];
		}
	}
	chingChongLog.push_back(output);
}