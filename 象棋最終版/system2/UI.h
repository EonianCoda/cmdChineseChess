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

//目前的畫面
enum  Screen {
	MainMenu, //主畫面
	Playing, //遊戲畫面
	Making, //自定義棋盤
};


namespace Setting {
	//顏色清單
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
		/****主選單的區塊****/
		/******************/

		Main, //初始畫面
		SelectMode, //選擇單人遊戲或雙人遊戲
		DuoPlayerMenu, //雙人遊戲清單
		SinglePlayerMenu, //單人遊戲清單
		SelectPlayer, //選擇誰先攻
		SelectSinglePlayer, //選擇電腦或玩家先攻
		Read, //讀取紀錄
		Read_Error, //讀取錯誤
		Option, //選項
		Sound, //音效

		/******************/
		/****遊戲內的區塊****/
		/******************/
		Log,
		ChessBoard,
		Status,
		Help,
		Pause,
		Regret,
		CannotRegret,
		ReturnMainMenu, //確定返回主選單
		Restart, //確定重新開始
		Victory, //勝利
		Store, //儲存遊戲

		/******************/
		/****畫棋盤的區塊****/
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
	void DrawHorizontalLine(Coordinate Start, int length,wchar_t element = L'═');
	void DrawVerticalLine(Coordinate Start, int length, wchar_t element = L'║');

	void clearLog();
	
	void showSaveData(vector<string>TXTFiles, int top);//byHans
	void clearData();//byHans
	void showDataPage(int now, int sum);//byHans
};

