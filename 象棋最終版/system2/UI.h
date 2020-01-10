#pragma once
#include<windows.h>
#include<iostream>
#include"ChessBoard.h"
#include<map>
#include<string>
using std::cout;
using std::wcout;
using std::endl;
using std::pair;
using std::map;
using std::make_pair;
using std::wstring;


typedef pair<int, int> Coordinate;

//�ثe���e��
enum  Screen {
	MainMenu, //�D�e��
	Playing, //�C���e��
	Making, //�۩w�q�ѽL
};


namespace Setting {
	//�C��M��
	enum Color {
		black = 0,
		blue = 1,
		green = 2,
		cyan = 3,
		red = 4,
		purple = 5,
		yellow = 6,
		white = 7,
		gray = 8,
	};

	enum Block {
		/******************/
		/****�D��檺�϶�****/
		/******************/

		Main, //��l�e��
		SelectMode, //��ܳ�H�C�������H�C��
		DuoPlayerMenu, //���H�C���M��
		SinglePlayerMenu, //��H�C���M��
		SelectPlayer, //��֥ܽ���
		SelectSinglePlayer, //��ܹq���Ϊ��a����
		Read, //Ū������
		Read_Error, //Ū�����~
		Option, //�ﶵ
		Sound, //����

		/******************/
		/****�C�������϶�****/
		/******************/
		Log,
		ChessBoard,
		Status,
		Help,
		Pause,
		Regret,
		CannotRegret,
		ReturnMainMenu, //�T�w��^�D���
		Restart, //�T�w���s�}�l
		Victory, //�ӧQ
		Store, //�x�s�C��

		/******************/
		/****�e�ѽL���϶�****/
		/******************/
		ChessNums,
		Selecting,
		Help_2,
		Warning,


	};
}


class UI {
	HANDLE handle;
	COORD CursorPos;

	int colorCode;
public:
	static UI* Instance;
	UI();
	~UI();

	void SetTextColor(Setting::Color front, Setting::Color back, bool frontLight = false, bool backLight = false);
	void SetTextColor(int colorCode);
	void CleanScreen();

	void gotoXY(int x, int y);
	void gotoXY(Coordinate pos);
	Coordinate getXY();
	void gotoBoardXY(Coordinate co);

	void showScreen(Screen screen);
	void showBlock(Screen screen, Setting::Block block);
	void showPlayer(int player);
	void showGeneral(bool on,int player = 0);
	void showSelectedChess(int chessNum);
	void showAdditionText(wstring text);
	void showLogPage(int, int);
	void ShowstartingScreen();
	void showLog(int, wstring&);

	void DrawBoard();
	void DrawFrame(Coordinate Start,int length,int width);
	void DrawHorizontalLine(Coordinate Start, int length,wchar_t element = L'��');
	void DrawVerticalLine(Coordinate Start, int length, wchar_t element = L'��');

	void clearLog();
	
	void showSaveData(vector<string>TXTFiles, int top);//byHans
	void clearData();//byHans
	void showDataPage(int now, int sum);//byHans
};

