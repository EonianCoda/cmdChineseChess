#include "Log.h"

namespace {
	wchar_t list[] = L"�@�N�h�H�����]��ӥK�ۨ��X���L";
	vector<wstring> order = { L"��e",L"�ᤤ�e",L"��T�G�e",L"��|�T�G�e" };
	wstring ChineseNumber = L"�@�@�G�T�|�����C�K�E";
	wstring Number = L"�@������������������";
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
		cout << "Log::getchingChongLog���~�G" << index << endl;
		return chingChongLog[0];
	}
}

//���chingChongLog����
int Log::getLength() const
{
	return (int)(chingChongLog.size());
}
pair<int, pair<Coordinate, Coordinate>>  Log::search(int n)
{
	return log[(n * 2) - 1];
}

//�[�J����Log
void Log::step(int chessNum, Coordinate from, Coordinate to)
{
	wstring output = L"";
	int count = 0, pos;

	//�YchessNum���X�k
	if (chessNum > 14 || chessNum < 0)
	{
		cout << "Log::step���~�G" << chessNum << endl;
		return;
	}

	//�M�䪽��W���X���ۦP���Ѥl
	for (int i = 0; i < 10; i++)
	{
		if (chessNum == ChessBoard::Instance->board[i][from.second])
		{
			//���n���ʪ������Ѥl
			if (from.first == i)
			{
				pos = count;
			}
			count++;

		}
	}

	output += to_wstring(chingChongLog.size() + 1);

	//�¤�
	if (chessNum < 8)
	{
		output += L" �¡G";
		//�Ĥ@�r
		if (count == 1) //�N��Ӹ��W�o�������Ѥl�Ȧ��@��
		{
			output += list[chessNum]; //�Ѥl
		}
		else
		{
			output += order[count - 2][pos];
		}

		output += L" "; //�Ů�
		//�ĤG�r
		if (count == 1)
		{
			output += Number[from.second + 1];//�[�J���ԧB�Ʀr
		}
		else
		{
			output += list[chessNum]; //�Ѥl
		}


		output += L" "; //�Ů�
		//�ĤT�r
		if (from.first == to.first)
		{
			output += L"��";
		}
		else if (to.first > from.first)
		{
			output += L"�i";
		}
		else if (to.first < from.first)
		{
			output += L"�h";
		}

		output += L" "; //�Ů�
		//�ĥ|�r
		if (from.second == to.second) //����
		{
			output += Number[abs(from.first - to.first)];
		}

		else //�צ�ξ��
		{
			output += Number[to.second + 1];
		}

	}
	//����
	else if (chessNum >= 8)
	{
		output += L" ���G";
		//�Ĥ@�r
		if (count == 1) //�N��Ӹ��W�o�������Ѥl�Ȧ��@��
		{
			output += list[chessNum];//�Ѥl
		}
		else
		{
			//�Y������A��V�n�˹L��
			pos = count - 1 - pos;
			output += order[count - 2][pos];
		}


		output += L" "; //�Ů�
		//�ĤG�r
		if (count == 1) //�N��Ӹ��W�o�������Ѥl�Ȧ��@��
		{
			output += ChineseNumber[10 - (from.second + 1)];//����~�r
		}
		else
		{
			output += list[chessNum];//�Ѥl
		}

		output += L" "; //�Ů�
		//�ĤT�r
		if (from.first == to.first)
		{
			output += L"��";
		}
		else if (to.first < from.first)
		{
			output += L"�i";
		}
		else if (to.first > from.first)
		{
			output += L"�h";
		}

		output += L" "; //�Ů�
		//�ĥ|�r
		if (from.second == to.second)//����
		{
			output += ChineseNumber[abs(from.first - to.first)];
			//chingChongLog.push_back(abs(from.first - to.first));//�e�i�B��  (�~)
		}
		//�צ�ξ��
		else
		{
			output += ChineseNumber[10 - (to.second + 1)];
		}
	}
	chingChongLog.push_back(output);
}