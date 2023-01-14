#include"Rule.h"

const vector<pair<int, int>> MOVE_LIST[15] = { {},
											   {make_pair(1,0),make_pair(-1,0),make_pair(0,1),make_pair(0,-1),make_pair(0,0)},//�N
											   {make_pair(1,1),make_pair(-1,1),make_pair(-1,-1),make_pair(1,-1)},//�h
											   {make_pair(2,2),make_pair(-2,2),make_pair(-2,-2),make_pair(2,-2)},//�H
											   {make_pair(0,0)},//��
											   {make_pair(1,2),make_pair(-1,2),make_pair(-1,-2),make_pair(1,-2),make_pair(2,1),make_pair(-2,1),make_pair(-2,-1),make_pair(2,-1)},//��
											   {make_pair(0,0)},//��
											   {make_pair(1,0),make_pair(0,1),make_pair(0,-1)},//��
											   {make_pair(1,0),make_pair(-1,0),make_pair(0,1),make_pair(0,-1),make_pair(0,0)},
											   {make_pair(1,1),make_pair(-1,1),make_pair(-1,-1),make_pair(1,-1)},
											   {make_pair(2,2),make_pair(-2,2),make_pair(-2,-2),make_pair(2,-2)},
											   {make_pair(0,0)},
											   {make_pair(1,2),make_pair(-1,2),make_pair(-1,-2),make_pair(1,-2),make_pair(2,1),make_pair(-2,1),make_pair(-2,-1),make_pair(2,-1)},
											   {make_pair(0,0)},
											   {make_pair(-1,0),make_pair(0,1),make_pair(0,-1)} };

pair<int, int> operator+(pair<int, int>p1, pair<int, int>p2)
{
	return make_pair(p1.first + p2.first, p1.second + p2.second);
}
pair<int, int> operator*(pair<int, int>p1, int c)
{
	return make_pair(p1.first *c, p1.second *c);
}
pair<int, int> operator/(pair<int, int>p1, int c)
{
	return make_pair(p1.first / c, p1.second / c);
}