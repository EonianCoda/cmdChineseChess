#pragma once
#include<vector>
#include<utility>
using namespace std;
typedef pair<int, int> Coordinate;
extern const vector<pair<int, int>> MOVE_LIST[15];
pair<int, int> operator+(pair<int, int>p1, pair<int, int>p2);
pair<int, int> operator*(pair<int, int>p1, int c);
pair<int, int> operator/(pair<int, int>p1, int c);